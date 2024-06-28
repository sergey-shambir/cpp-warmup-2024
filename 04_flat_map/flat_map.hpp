#pragma once

#include <vector>
#include <utility>
#include <optional>

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

    std::optional<Value> Get(const Key &key) const
    {
        const auto it = BinarySearchGreaterOrEqual(key);
        if (it == data.end() || it->first != key)
        {
            return std::nullopt;
        }
        return it->second;
    }

private:
    using Vector = typename std::vector<KeyValue>;
    using ConstIterator = typename Vector::const_iterator;

    ConstIterator BinarySearchGreaterOrEqual(const Key &key) const
    {
        ConstIterator left = data.begin();
        ConstIterator right = data.end();

        while (left != right)
        {
            ConstIterator middle = left + std::distance(left, right) / 2;
            if (middle->first < key)
            {
                left = middle;
                ++left;
            }
            else
            {
                right = middle;
            }

        } while (left != right);

        return left;
    }

    Vector data;
};
