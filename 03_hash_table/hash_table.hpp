#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <vector>
#include <memory>

std::size_t HashKey(std::uint32_t key);

std::size_t HashKey(const std::string &key);

class StringHashTable
{
public:
    StringHashTable();
    ~StringHashTable();

    StringHashTable(const StringHashTable &) = delete;

    std::size_t Size() const;

    std::size_t Capacity() const;

    void Add(std::string &&key, std::string &&value);

    void Delete(const std::string &key);

    std::optional<std::string> Get(const std::string &key) const;

private:
    void Rehash(std::size_t capacity);

    class State;

    std::unique_ptr<State> state;
};
