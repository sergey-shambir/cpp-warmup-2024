#pragma once

#include <vector>
#include <utility>
#include <optional>
#include <algorithm>

template <class Value>
class FlatSet
{
public:
    std::size_t Size() const
    {
        return data.size();
    }

    std::size_t Capacity() const
    {
        return data.capacity();
    }

    void Add(Value value)
    {
        const auto it = std::ranges::partition_point(data, [&value] (const Value &item) {
            return item < value;
        });
        if (it == data.end() || *it != value)
        {
            data.insert(it, std::forward<Value>(value));
        }
    }

    void Delete(const Value &value)
    {
        const auto it = std::ranges::partition_point(data, [&value] (const Value &item) {
            return item < value;
        });
        if (it != data.end() && *it == value)
        {
            data.erase(it);
        }
    }

    bool Contains(const Value &value) const
    {
        const auto it = std::ranges::partition_point(data, [&value] (const Value &item) {
            return item < value;
        });
        if (it != data.end() && *it == value)
        {
            return true;
        }
        return false;

    }

private:
    std::vector<Value> data;
};
