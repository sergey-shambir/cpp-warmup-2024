#include "hash_table.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("HashKey from uint32_t calculated")
{
    REQUIRE(HashKey(0) == 843253);
    REQUIRE(HashKey(17) == 3006452);
    REQUIRE(HashKey(9001) == 1146193500);
}

TEST_CASE("HashKey from string calculated")
{
    REQUIRE(HashKey("banana") == 8020756741749873380); // 64-bit hash value
}

TEST_CASE("Empty StringHashTable has capacity 8 and no values")
{
    StringHashTable table;
    REQUIRE(table.Size() == 0);
    REQUIRE(table.Capacity() == 8);
    REQUIRE(table.Get("banana") == std::nullopt);
}

TEST_CASE("StringHashTable adds 9 strings")
{
    StringHashTable table;

    table.Add("banana", "fruit");
    table.Add("apple", "fruit");
    table.Add("potato", "vegetable");
    table.Add("dog", "animal");

    REQUIRE(table.Size() == 4);
    REQUIRE(table.Capacity() == 8);
    REQUIRE(table.Get("banana") == "fruit");
    REQUIRE(table.Get("apple") == "fruit");
    REQUIRE(table.Get("tomato") == std::nullopt);
    REQUIRE(table.Get("potato") == "vegetable");
    REQUIRE(table.Get("dog") == "animal");
    REQUIRE(table.Get("cat") == std::nullopt);

    table.Add("cat", "animal");
    table.Add("turtle", "animal");
    table.Add("snail", "animal");
    table.Add("hamster", "animal");

    REQUIRE(table.Size() == 8);
    REQUIRE(table.Capacity() == 16); // Rehash occured.
    // Preserved old data after rehash
    REQUIRE(table.Get("apple") == "fruit");
    REQUIRE(table.Get("tomato") == std::nullopt);
    REQUIRE(table.Get("potato") == "vegetable");
    // Added new data
    REQUIRE(table.Get("cat") == "animal");
    REQUIRE(table.Get("turtle") == "animal");
    REQUIRE(table.Get("snail") == "animal");
    REQUIRE(table.Get("hamster") == "animal");

    table.Add("tomato", "vegetable");

    REQUIRE(table.Size() == 9);
    REQUIRE(table.Capacity() == 32); // Rehash occured.
    // Preserved old data after rehash
    REQUIRE(table.Get("apple") == "fruit");
    REQUIRE(table.Get("cat") == "animal");
    REQUIRE(table.Get("snail") == "animal");
    // Added new data
    REQUIRE(table.Get("tomato") == "vegetable");
    REQUIRE(table.Get("horse") == std::nullopt);
}

TEST_CASE("StringHashTable adds and deletes strings")
{
    StringHashTable table;

    table.Add("banana", "fruit");
    table.Add("apple", "fruit");
    table.Add("potato", "vegetable");
    table.Add("dog", "animal");
    REQUIRE(table.Size() == 4);
    REQUIRE(table.Capacity() == 8);

    table.Delete("banana");
    REQUIRE(table.Size() == 3);
    REQUIRE(table.Capacity() == 8);

    table.Delete("dog");
    REQUIRE(table.Size() == 2);
    REQUIRE(table.Capacity() == 8);

    table.Add("dog", "animal");

    REQUIRE(table.Size() == 3);
    REQUIRE(table.Capacity() == 16);
    REQUIRE(table.Get("banana") == std::nullopt);
    REQUIRE(*table.Get("apple") == "fruit");
    REQUIRE(table.Get("tomato") == std::nullopt);
    REQUIRE(*table.Get("potato") == "vegetable");
    REQUIRE(table.Get("dog") == "animal");
    REQUIRE(table.Get("cat") == std::nullopt);
}
