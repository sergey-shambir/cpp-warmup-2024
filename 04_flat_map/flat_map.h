#pragma once

#include <vector>
#include <optional>
#include <algorithm>

template <class Key, class Value>
class FlatMap
{
public:
    using KeyValue = std::pair<Key, Value>;
    using KeyValueArray = std::vector<KeyValue>;
    using ConstIterator = KeyValueArray::const_iterator;

    std::size_t Size() const
    {
        return data.size();
    }

    std::size_t Capacity() const
    {
        return data.capacity();
    }

    ConstIterator begin() const
    {
        return data.cbegin();
    }

    ConstIterator end() const
    {
        return data.cend();
    }

    std::optional<Value> Get(const Key &key) const
    {
        const auto it = std::ranges::partition_point(data, [&key] (const KeyValue &pair) {
            return pair.first < key;
        });
        if (it != data.end() && it->first == key)
        {
            return it->second;
        }
        return std::nullopt;
    }

    bool Contains(const Key &key) const
    {
        const auto it = std::ranges::partition_point(data, [&key] (const KeyValue &pair) {
            return pair.first < key;
        });
        if (it != data.end() && it->first == key)
        {
            return true;
        }
        return false;

    }

    void Add(const Key &key, const Value &value)
    {
        const auto it = std::ranges::partition_point(data, [&key] (const KeyValue &pair) {
            return pair.first < key;
        });
        if (it != data.end() && it->first == key)
        {
            it->second = value;
        }
        else
        {
            data.insert(it, {key, value});
        }
    }

    void Delete(const Key &key)
    {
        const auto it = std::ranges::partition_point(data, [&key] (const KeyValue &pair) {
            return pair.first < key;
        });
        if (it != data.end() && it->first == key)
        {
            data.erase(it);
        }
    }

private:
    KeyValueArray data;
};
