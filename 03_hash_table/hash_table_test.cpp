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

TEST_CASE("StringHashTable adds 4 strings")
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
}
