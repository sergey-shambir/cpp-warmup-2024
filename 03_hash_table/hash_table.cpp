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

StringHashTable::StringHashTable()
    : data(INITIAL_HASH_TABLE_CAPACITY, std::nullopt)
{
}

std::size_t StringHashTable::Size() const
{
    return size;
}

std::size_t StringHashTable::Capacity() const
{
    return data.size();
}

void StringHashTable::Add(std::string &&key, std::string &&value)
{
    if (2 * size >= data.size())
    {
        Reserve(2 * data.size());
    }

    if (AddImpl(data, std::forward<std::string>(key), std::forward<std::string>(value)))
    {
        ++size;
    }
}

std::optional<std::string> StringHashTable::Get(const std::string &key) const
{
    const std::size_t capacity = data.size();
    std::size_t position = HashKey(key) % capacity;

    const std::optional<KeyValue> *next = data.data() + position;
    const std::optional<KeyValue> *end = data.data() + capacity;

    for (; next < end; ++next)
    {
        const auto &keyValue = *next;
        if (!keyValue.has_value())
        {
            return std::nullopt;
        }
        if (keyValue->first == key)
        {
            return keyValue->second;
        }
    }
    return std::nullopt;
}

bool StringHashTable::AddImpl(std::vector<std::optional<KeyValue>> &destination, std::string &&key, std::string &&value)
{
    const std::size_t capacity = destination.size();
    std::size_t startPosition = HashKey(key) % capacity;

    std::size_t position = startPosition;
    do
    {
        std::optional<KeyValue> &keyValue = destination[position];
        if (keyValue.has_value())
        {
            if (keyValue->first == key)
            {
                return false; // Already added
            }
            position = (position + 1) % capacity;
        }
        else
        {
            keyValue.emplace(std::forward<std::string>(key), std::forward<std::string>(value));
            return true;
        }
    } while (position != startPosition);

    throw std::logic_error("failed to insert value on position " + std::to_string(position));
}

void StringHashTable::Reserve(size_t capacity)
{
    assert(capacity > data.size());

    std::vector<std::optional<KeyValue>> newData(capacity, std::nullopt);
    for (std::optional<KeyValue> &keyValue : data)
    {
        if (keyValue.has_value())
        {
            AddImpl(newData, std::move(keyValue->first), std::move(keyValue->second));
        }
    }
    data = newData;
}
