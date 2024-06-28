#pragma once

#include <cstdint>
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
    using KeyValue = std::pair<std::string, std::string>;

    const std::size_t KeyValueSize = sizeof(KeyValue);

    StringHashTable();

    StringHashTable(const StringHashTable &) = delete;

    std::size_t Size() const;

    std::size_t Capacity() const;

    void Add(std::string &&key, std::string &&value);

    std::optional<std::string> Get(const std::string &key) const;

private:
    static bool AddImpl(std::vector<std::optional<KeyValue>> &destination, std::string &&key, std::string &&value);

    void Reserve(size_t capacity);

    size_t size = 0;
    std::vector<std::optional<KeyValue>> data;
};
