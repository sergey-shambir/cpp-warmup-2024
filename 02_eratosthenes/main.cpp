#include <vector>
#include <ranges>
#include <cmath>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

using Catch::Matchers::Equals;

unsigned EstimatePrimeNumbersCount(unsigned maxNumber)
{
    if (maxNumber < 10)
    {
        return 4;
    }

    // According to the Prime Number Theorem, prime numbers count in range [1...n] asymptotically tends to `n / ln(n)`
    const unsigned lnMaxNumber = static_cast<unsigned>(std::log(static_cast<double>(maxNumber)));

    return maxNumber / lnMaxNumber;
}

std::vector<unsigned> ListPrimeNumbers(unsigned maxNumber)
{
    if (maxNumber <= 1)
    {
        return std::vector<unsigned>();
    }

    std::vector<unsigned> results;
    results.reserve(static_cast<size_t>(8 + EstimatePrimeNumbersCount(maxNumber)));

    // In this sieve, `index = number - 1` and `true` means "may be prime number"
    std::vector<bool> sieve(static_cast<size_t>(maxNumber), true);
    const size_t sieveSize = sieve.size();

    const size_t maxNumberRoot = static_cast<size_t>(std::sqrt(maxNumber));
    for (size_t number = 2; number <= maxNumberRoot; ++number)
    {
        size_t index = number - 1;
        if (sieve[index])
        {
            results.push_back(static_cast<unsigned>(number));
        }
        for (; index < sieveSize; index += number)
        {
            sieve[index] = false;
        }
    }
    for (size_t index = maxNumberRoot; index < sieveSize; ++index)
    {
        if (sieve[index])
        {
            results.push_back(static_cast<unsigned>(index + 1));
        }
    }

    return results;
}

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
