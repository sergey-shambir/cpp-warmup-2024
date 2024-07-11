#include "solution.h"

#include <iostream>

int main()
{
    const int result = countAchievableCells({ 1000, 1000 }, 25);
    std::cout << result << " cells are achievable from (1000, 1000)" << std::endl;
}
