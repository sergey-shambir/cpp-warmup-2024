#include "solution.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Own examples")
{
    REQUIRE(maxSubarrayLength({ 0, 1, 1, 1, 0, 0, 1, 1, 0 }, 1) == 4);
    REQUIRE(maxSubarrayLength({ 0, 1, 1, 1, 0, 0, 1, 1, 0 }, 2) == 7);
    REQUIRE(maxSubarrayLength({ 0, 1, 1, 1, 0, 0, 1, 1, 0 }, 3) == 8);
    REQUIRE(maxSubarrayLength({ 0, 1, 1, 1, 0, 0, 1, 1, 0 }, 4) == 9);
    REQUIRE(maxSubarrayLength({ 0, 1, 1, 1, 0, 0, 1, 1, 0 }, 5) == 9);
    REQUIRE(maxSubarrayLength({ 0, 1, 1, 1, 0, 0, 1, 1, 0 }, 6) == 9);

    REQUIRE(maxSubarrayLength({}, 2) == 0);
    REQUIRE(maxSubarrayLength({ 1 }, 0) == 1);
    REQUIRE(maxSubarrayLength({ 0 }, 0) == 0);
    REQUIRE(maxSubarrayLength({ 0 }, 1) == 1);
}
