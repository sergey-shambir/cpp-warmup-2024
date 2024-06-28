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
