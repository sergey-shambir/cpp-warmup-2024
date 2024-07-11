#include "solution.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Trivial cases")
{
    REQUIRE(countAchievableCells({ 0, 0 }, 0) == 1);
    REQUIRE(countAchievableCells({ 0, 0 }, 1) == 5);
    REQUIRE(countAchievableCells({ 0, 1 }, 1) == 5);
    REQUIRE(countAchievableCells({ 1, 1 }, 2) == 13);
    REQUIRE(countAchievableCells({ 0, 0 }, 2) == 13);
}
