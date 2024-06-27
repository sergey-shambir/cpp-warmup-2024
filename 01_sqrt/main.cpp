#include <iostream>
#include <utility>
#include <cmath>
#include <cstdio>

#include <catch2/catch_test_macros.hpp>

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

int main()
{
    std::printf("%f\n", Sqrt(2.0));
}
