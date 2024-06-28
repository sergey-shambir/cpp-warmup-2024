#include "hash_table.hpp"
#include <stdexcept>
#include <cassert>

constexpr std::size_t HASH_FACTOR = 127247;
constexpr std::size_t HASH_ADDENUM = 843253;

constexpr std::size_t INITIAL_HASH_TABLE_CAPACITY = 8;

std::size_t HashKey(std::uint32_t key)
{
    return HASH_FACTOR * key + HASH_ADDENUM;
}

std::size_t HashKey(const std::string &key)
{
    constexpr std::size_t batchSize = sizeof(std::uint32_t) / sizeof(char);
    const std::size_t batchCount = key.size() / batchSize;

    // Hash in batches, each batch contains 4 chars (bytes)
    const std::uint32_t *batch = reinterpret_cast<const std::uint32_t *>(key.data());
    const std::uint32_t *endBatch = batch + batchCount;

    std::size_t result = 0;
    for (; batch < endBatch; ++batch)
    {
        result = HASH_FACTOR * (result + *batch) + HASH_ADDENUM;
    }

    // Hash remaining chars.
    std::uint32_t lastBatch;
    const char *source = reinterpret_cast<const char *>(batch);
    const char *end = source + batchSize;
    char *target = reinterpret_cast<char *>(&lastBatch);

    for (; source < end; ++source, ++target)
    {
        *target = *source;
    }

    result = HASH_FACTOR * (result + lastBatch) + HASH_ADDENUM;

    return result;
}

class StringHashTable::State
{
public:
    struct Item
    {
        std::string key;
        std::string value;
        bool used = false;       // Contains key/value pair
        bool searchable = false; // Contains key/value pair or previously contained but removed now

        void Emplace(std::string &&key, std::string &&value)
        {
            used = true;
            searchable = true;
            this->key = std::forward<std::string>(key);
            this->value = std::forward<std::string>(value);
        }

        void Delete()
        {
            used = false;
            key = std::string();
            value = std::string();
        }
    };

    State(size_t capacity)
        : items(capacity, Item{})
    {
    }

    size_t UsedCount() const
    {
        return usedCount;
    }

    size_t Capacity() const
    {
        return items.size();
    }

    std::optional<std::string> Get(const std::string &key) const
    {
        const std::size_t capacity = items.size();
        const std::size_t startPosition = HashKey(key) % capacity;

        std::size_t position = startPosition;
        do
        {
            const Item &item = items[position];
            if (!item.searchable)
            {
                return std::nullopt;
            }
            if (item.used && item.key == key)
            {
                return item.value;
            }
            position = (position + 1) % capacity;
        } while (position != startPosition);

        return std::nullopt;
    }

    bool Add(std::string &&key, std::string &&value)
    {
        const std::size_t capacity = items.size();
        const std::size_t startPosition = HashKey(key) % capacity;

        std::size_t position = startPosition;
        do
        {
            Item &item = items[position];
            if (item.used)
            {
                if (item.key == key)
                {
                    return false; // Hash already contains this key-value pair
                }
                position = (position + 1) % capacity;
            }
            else
            {
                const bool wasSearchable = item.searchable;
                item.Emplace(std::forward<std::string>(key), std::forward<std::string>(value));

                ++usedCount;
                if (!wasSearchable)
                {
                    ++searchableCount;
                }

                return true;
            }
        } while (position != startPosition);

        throw std::logic_error("failed to insert value on position " + std::to_string(position));
    }

    void Delete(const std::string &key)
    {
        const std::size_t capacity = items.size();
        const std::size_t startPosition = HashKey(key) % capacity;

        std::size_t position = startPosition;
        do
        {
            Item &item = items[position];
            if (!item.searchable)
            {
                return; // Not found
            }
            if (item.used && item.key == key)
            {
                item.Delete();
                --usedCount;
                return;
            }
            position = (position + 1) % capacity;
        } while (position != startPosition);
    }

    bool ShouldRehashBeforeAdd() const
    {
        return 2 * searchableCount >= items.size();
    }

    void MoveItemsTo(State &newState)
    {
        for (Item &item : items)
        {
            if (item.used)
            {
                newState.Add(std::move(item.key), std::move(item.value));
            }
        }
    }

private:
    size_t usedCount = 0;
    size_t searchableCount = 0;
    std::vector<Item> items;
};

StringHashTable::StringHashTable()
    : state(new State(INITIAL_HASH_TABLE_CAPACITY))
{
}

StringHashTable::~StringHashTable()
{
}

std::size_t StringHashTable::Size() const
{
    return state->UsedCount();
}

std::size_t StringHashTable::Capacity() const
{
    return state->Capacity();
}

void StringHashTable::Add(std::string &&key, std::string &&value)
{
    if (state->ShouldRehashBeforeAdd())
    {
        Rehash(2 * state->Capacity());
    }
    state->Add(std::forward<std::string>(key), std::forward<std::string>(value));
}

void StringHashTable::Delete(const std::string &key)
{
    state->Delete(key);
}

std::optional<std::string> StringHashTable::Get(const std::string &key) const
{
    return state->Get(key);
}

void StringHashTable::Rehash(std::size_t capacity)
{
    assert(capacity > state->Capacity());

    auto newState = std::make_unique<State>(capacity);
    state->MoveItemsTo(*newState);
    std::swap(state, newState);
}
