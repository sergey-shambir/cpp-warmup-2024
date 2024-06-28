#include "flat_map.hpp"
#include <string>
#include <catch2/catch_test_macros.hpp>


TEST_CASE("FlatMap<int,string> can add values")
{
    FlatMap<int,std::string> map;
    map.Add(5, std::string("pear"));
    map.Add(10, std::string("banana"));
    map.Add(7, std::string("apple"));

    REQUIRE(map.Get(1) == std::nullopt);
    REQUIRE(map.Get(5) == "pear");
    REQUIRE(map.Get(7) == "apple");
    REQUIRE(map.Get(10) == "banana");
    REQUIRE(map.Get(11) == std::nullopt);
}


TEST_CASE("FlatMap<string,string> can add values")
{
    FlatMap<std::string,std::string> map;

    map.Add("banana", "fruit");
    map.Add("apple", "fruit");
    map.Add("potato", "vegetable");
    map.Add("dog", "animal");

    REQUIRE(map.Size() == 4);
    REQUIRE(map.Get("banana") == "fruit");
    REQUIRE(map.Get("apple") == "fruit");
    REQUIRE(map.Get("tomato") == std::nullopt);
    REQUIRE(map.Get("potato") == "vegetable");
    REQUIRE(map.Get("dog") == "animal");
    REQUIRE(map.Get("cat") == std::nullopt);

    map.Add("cat", "animal");
    map.Add("turtle", "animal");
    map.Add("snail", "animal");
    map.Add("hamster", "animal");

    REQUIRE(map.Size() == 8);
    // Preserved old data after rehash
    REQUIRE(map.Get("apple") == "fruit");
    REQUIRE(map.Get("tomato") == std::nullopt);
    REQUIRE(map.Get("potato") == "vegetable");
    // Added new data
    REQUIRE(map.Get("cat") == "animal");
    REQUIRE(map.Get("turtle") == "animal");
    REQUIRE(map.Get("snail") == "animal");
    REQUIRE(map.Get("hamster") == "animal");

    map.Add("tomato", "vegetable");

    REQUIRE(map.Size() == 9);
    // Preserved old data after rehash
    REQUIRE(map.Get("apple") == "fruit");
    REQUIRE(map.Get("cat") == "animal");
    REQUIRE(map.Get("snail") == "animal");
    // Added new data
    REQUIRE(map.Get("tomato") == "vegetable");
    REQUIRE(map.Get("horse") == std::nullopt);
}

TEST_CASE("FlatMap<string,string> can add and delete")
{
    FlatMap<std::string,std::string> map;

    map.Add("banana", "fruit");
    map.Add("apple", "fruit");
    map.Add("potato", "vegetable");
    map.Add("dog", "animal");
    REQUIRE(map.Size() == 4);

    map.Delete("banana");
    REQUIRE(map.Size() == 3);

    map.Delete("dog");
    REQUIRE(map.Size() == 2);

    map.Add("dog", "animal");

    REQUIRE(map.Size() == 3);
    REQUIRE(map.Get("banana") == std::nullopt);
    REQUIRE(*map.Get("apple") == "fruit");
    REQUIRE(map.Get("tomato") == std::nullopt);
    REQUIRE(*map.Get("potato") == "vegetable");
    REQUIRE(map.Get("dog") == "animal");
    REQUIRE(map.Get("cat") == std::nullopt);
}
