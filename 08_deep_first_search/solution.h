
#include <vector>
#include <utility>

using Point = typename std::pair<size_t, size_t>; // (x, y)

bool canAchievePoint(const std::vector<std::vector<size_t>> &cells, Point from, Point to);
