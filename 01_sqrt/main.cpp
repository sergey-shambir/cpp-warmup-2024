#include <iostream>
#include <utility>
#include <cmath>
#include <cstdio>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinAbs;

double Sqrt(double x)
{
    double result = 1.0;
    double epsilon = 0.1e-8 * std::max(x, 1.0);

    while (true)
    {
        double square_miss = result * result - x;
        double correction = square_miss / (2.0 * result);
        result -= correction;

        if (std::abs(correction) < epsilon)
        {
            return result;
        }
    }
}

TEST_CASE("Sqrt calculated")
{
    double epsilon = 0.1e-8;

    REQUIRE_THAT(Sqrt(1.0), WithinAbs(1.0, epsilon));
    REQUIRE_THAT(Sqrt(4.0), WithinAbs(2.0, epsilon));
    REQUIRE_THAT(Sqrt(11.56), WithinAbs(3.4, epsilon));
    REQUIRE_THAT(Sqrt(0.49), WithinAbs(0.7, epsilon));
    REQUIRE_THAT(Sqrt(0.0), WithinAbs(0.0, epsilon));
}
