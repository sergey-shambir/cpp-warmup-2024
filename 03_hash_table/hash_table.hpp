#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <vector>

std::size_t HashKey(std::uint32_t key);

std::size_t HashKey(const std::string &key);

class StringHashTable
{
public:
    StringHashTable();

    StringHashTable(const StringHashTable &) = delete;

    std::size_t Size() const;

    std::size_t Capacity() const;

    void Add(std::string &&key, std::string &&value);

    std::optional<std::string> Get(const std::string &key) const;

private:
    struct Item
    {
        std::string key;
        std::string value;
        bool used = false; // Contains key/value pair
        bool searchable = false; // Contains key/value pair or previously contained but removed now
    };

    static bool AddImpl(std::vector<Item> &destination, std::string &&key, std::string &&value);

    void Reserve(size_t capacity);

    size_t usedSize = 0;
    std::vector<Item> data;
};
