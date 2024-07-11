#pragma once

#include <utility>
#include <cstdint>

using Point = typename std::pair<std::int32_t,std::int32_t>;

std::uint32_t countAchievableCells(Point p, std::uint32_t maxDigitsSum);
