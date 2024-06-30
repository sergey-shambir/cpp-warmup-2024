#pragma once

#include <vector>
#include <utility>
#include <optional>
#include <algorithm>

template <class Key, class Value>
class FlatMap
{
public:
    using KeyValue = std::pair<Key, Value>;

    std::size_t Size() const
    {
        return data.size();
    }

    std::size_t Capacity() const
    {
        return data.capacity();
    }

    void Add(Key &&key, Value &&value)
    {
        const auto it = BinarySearchGreaterOrEqual(key);
        data.insert(it, {std::forward<Key>(key), std::forward<Value>(value)});
    }

    void Delete(const Key &key)
    {
        const auto it = BinarySearchGreaterOrEqual(key);
        if (it != data.end() && it->first == key)
        {
            data.erase(it);
        }
    }

    std::optional<Value> Get(const Key &key) const
    {
        const auto it = BinarySearchGreaterOrEqual(key);
        if (it != data.end() && it->first == key)
        {
            return it->second;
        }
        return std::nullopt;
    }

private:
    using Vector = typename std::vector<KeyValue>;
    using ConstIterator = typename Vector::const_iterator;

    ConstIterator BinarySearchGreaterOrEqual(const Key &key) const
    {
        return std::partition_point(data.begin(), data.end(), [&key] (const KeyValue &pair) {
            return pair.first < key;
        });
    }

    Vector data;
};
