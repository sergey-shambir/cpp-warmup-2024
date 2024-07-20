#include "AvlTreeMap.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

using Catch::Matchers::Equals;

TEST_CASE("AvlTreeMap<std::string,std::string> can insert")
{
    AvlTreeMap<std::string, std::string> m;
    m.Insert("banana", "fruit");
    m.Insert("coconut", "fruit");
    m.Insert("potato", "vegetable");
    m.Insert("dog", "animal");
}

TEST_CASE("AvlTreeMap<int,std::string> can insert and remove")
{
    AvlTreeMap<int, std::string> map;
    map.Insert(10, "banana");

    REQUIRE_THAT(map.ListKeys(), Equals(std::vector<int>{ 10 }));
    REQUIRE_THAT(map.ListValues(), Equals(std::vector<std::string>{ "banana" }));

    map.Insert(12, "coconut");
    map.Insert(3, "cherry");

    REQUIRE_THAT(map.ListKeys(), Equals(std::vector<int>{ 3, 10, 12 }));
    REQUIRE_THAT(map.ListValues(), Equals(std::vector<std::string>{ "cherry", "banana", "coconut" }));

    map.Insert(7, "blueberry");
    map.Insert(1, "lemon");
    map.Insert(4, "pineapple");
    map.Insert(15, "pear");

    REQUIRE_THAT(map.ListKeys(), Equals(std::vector<int>{ 1, 3, 4, 7, 10, 12, 15 }));
    REQUIRE_THAT(map.ListValues(), Equals(std::vector<std::string>{ "lemon", "cherry", "pineapple", "blueberry", "banana", "coconut", "pear" }));

    map.Remove(3);

    REQUIRE_THAT(map.ListKeys(), Equals(std::vector<int>{ 1, 4, 7, 10, 12, 15 }));
    REQUIRE_THAT(map.ListValues(), Equals(std::vector<std::string>{ "lemon", "pineapple", "blueberry", "banana", "coconut", "pear" }));

    map.Remove(10);
    map.Remove(7);
    map.Remove(12);

    REQUIRE_THAT(map.ListKeys(), Equals(std::vector<int>{ 1, 4, 15 }));
    REQUIRE_THAT(map.ListValues(), Equals(std::vector<std::string>{ "lemon", "pineapple", "pear" }));

    map.Insert(7, "raspberry");
    map.Insert(8, "strawberry");
    map.Remove(1);

    REQUIRE_THAT(map.ListKeys(), Equals(std::vector<int>{ 4, 7, 8, 15 }));
    REQUIRE_THAT(map.ListValues(), Equals(std::vector<std::string>{ "pineapple", "raspberry", "strawberry", "pear" }));
}
