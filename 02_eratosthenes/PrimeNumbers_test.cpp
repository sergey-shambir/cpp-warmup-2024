#include "PrimeNumbers.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

using Catch::Matchers::Equals;

TEST_CASE("No prime numbers up to 1")
{
    REQUIRE_THAT(ListPrimeNumbers(1), Equals(std::vector<unsigned>{}));
}

TEST_CASE("One prime number up to 2")
{
    REQUIRE_THAT(ListPrimeNumbers(2), Equals(std::vector<unsigned>{2}));
}

TEST_CASE("Two prime numbers up to 3")
{
    REQUIRE_THAT(ListPrimeNumbers(3), Equals(std::vector<unsigned>{2, 3}));
}

TEST_CASE("Prime numbers calculated up to 11")
{
    REQUIRE_THAT(ListPrimeNumbers(11), Equals(std::vector<unsigned>{2, 3, 5, 7, 11}));
}

TEST_CASE("Prime numbers calculated up to 20")
{
    REQUIRE_THAT(ListPrimeNumbers(20), Equals(std::vector<unsigned>{2, 3, 5, 7, 11, 13, 17, 19}));
}

TEST_CASE("Prime numbers calculated up to 100")
{
    REQUIRE_THAT(ListPrimeNumbers(100), Equals(std::vector<unsigned>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}));
}

TEST_CASE("Prime numbers calculated up to 1000000")
{
    const auto primes = ListPrimeNumbers(1000000);
    REQUIRE(primes.front() == 2);
    REQUIRE(primes.back() == 999983);
    REQUIRE(primes.size() == 78498);
}
