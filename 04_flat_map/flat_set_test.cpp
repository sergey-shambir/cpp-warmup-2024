#include "flat_set.h"
#include <string>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("FlatSet<int> can add values")
{
    FlatSet<int> map;
    map.Add(11);
    map.Add(17);
    map.Add(101);

    REQUIRE(!map.Contains(15));
    REQUIRE(map.Contains(101));
    REQUIRE(map.Contains(11));
    REQUIRE(map.Contains(17));
    REQUIRE(!map.Contains(100));
}

TEST_CASE("FlatSet<string> can add values")
{
    FlatSet<std::string> map;

    map.Add("banana");
    map.Add("apple");
    map.Add("potato");
    map.Add("dog");

    REQUIRE(map.Size() == 4);

    REQUIRE(map.Contains("banana"));
    REQUIRE(map.Contains("apple"));
    REQUIRE(!map.Contains("tomato"));
    REQUIRE(map.Contains("potato"));
    REQUIRE(map.Contains("dog"));
    REQUIRE(!map.Contains("cat"));

    map.Add("cat");
    map.Add("turtle");
    map.Add("snail");
    map.Add("hamster");

    REQUIRE(map.Size() == 8);
    // Preserved old data
    REQUIRE(map.Contains("apple"));
    REQUIRE(!map.Contains("tomato"));
    REQUIRE(map.Contains("potato"));
    // Added new data
    REQUIRE(map.Contains("cat"));
    REQUIRE(map.Contains("turtle"));
    REQUIRE(map.Contains("snail"));
    REQUIRE(map.Contains("hamster"));

    map.Add("tomato");

    REQUIRE(map.Size() == 9);
    // Preserved old data
    REQUIRE(map.Contains("apple"));
    REQUIRE(map.Contains("cat"));
    REQUIRE(map.Contains("snail"));
    // Added new data
    REQUIRE(map.Contains("tomato"));
    REQUIRE(!map.Contains("horse"));
}

TEST_CASE("FlatSet<string> can add and delete")
{
    FlatSet<std::string> map;

    map.Add("banana");
    map.Add("apple");
    map.Add("potato");
    map.Add("dog");
    REQUIRE(map.Size() == 4);

    map.Delete("banana");
    REQUIRE(map.Size() == 3);

    map.Delete("dog");
    REQUIRE(map.Size() == 2);

    map.Add("dog");

    REQUIRE(map.Size() == 3);
    REQUIRE(!map.Contains("banana"));
    REQUIRE(map.Contains("apple"));
    REQUIRE(!map.Contains("tomato"));
    REQUIRE(map.Contains("potato"));
    REQUIRE(map.Contains("dog"));
    REQUIRE(!map.Contains("cat"));
}
