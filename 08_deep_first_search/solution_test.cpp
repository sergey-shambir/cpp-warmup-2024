#include "solution.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Example from interview")
{
    std::vector<std::vector<size_t>> cells{
        { 6, 4, 6, 3, 4, 7, 7, 5, 3, 3 },
        { 9, 3, 4, 3, 6, 7, 5, 8, 2, 5 },
        { 3, 2, 7, 3, 7, 3, 7, 2, 6, 4 },
        { 6, 7, 4, 7, 6, 7, 8, 8, 2, 2 },
        { 3, 3, 2, 8, 6, 7, 3, 3, 1, 8 },
        { 7, 4, 7, 4, 4, 5, 8, 6, 1, 6 },
        { 4, 7, 6, 8, 4, 7, 7, 7, 2, 3 },
        { 3, 1, 5, 3, 4, 2, 7, 2, 5, 6 },
        { 2, 4, 4, 9, 8, 3, 8, 6, 7, 8 },
        { 1, 2, 4, 3, 5, 1, 5, 9, 6, 6 }
    };

    REQUIRE(canAchievePoint(cells, {0, 0}, {6, 0}));
    REQUIRE(canAchievePoint(cells, {0, 0}, {6, 7}));
    REQUIRE(canAchievePoint(cells, {0, 0}, {0, 7}));
    REQUIRE(!canAchievePoint(cells, {1, 1}, {10, 6}));
}
