#include "PrimeNumbers.h"

#include <cmath>

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
