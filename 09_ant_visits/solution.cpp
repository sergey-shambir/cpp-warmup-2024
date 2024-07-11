#include "solution.h"

#include <cmath>
#include <stack>
#include <unordered_set>

namespace
{
struct PointHash
{
    std::size_t operator()(const Point& p) const
    {
        return std::hash<std::int64_t>()(std::int64_t(p.first) << 32 + p.second);
    }
};

std::uint32_t getDigitsSum(std::int32_t number)
{
    number = std::abs(number);
    int sum = 0;
    while (number)
    {
        sum += number % 10;
        number /= 10;
    }

    return sum;
}

std::uint32_t getDigitsSum(Point p)
{
    return getDigitsSum(p.first) + getDigitsSum(p.second);
}
} // namespace

std::uint32_t countAchievableCells(Point p, std::uint32_t maxDigitsSum)
{
    std::stack<Point> toBeVisited;
    std::unordered_set<Point, PointHash> visited;

    toBeVisited.push(p);

    while (!toBeVisited.empty())
    {
        const Point p = toBeVisited.top();
        toBeVisited.pop();

        if (getDigitsSum(p) > maxDigitsSum || visited.contains(p))
        {
            continue;
        }
        visited.insert(p);

        toBeVisited.push({ p.first - 1, p.second });
        toBeVisited.push({ p.first + 1, p.second });
        toBeVisited.push({ p.first, p.second - 1 });
        toBeVisited.push({ p.first, p.second + 1 });
    }

    return std::uint32_t(visited.size());
}
