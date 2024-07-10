#include "solution.h"

class Finder
{
public:
    explicit Finder(const std::vector<std::vector<size_t>>& cells)
        : cells(cells)
        , height(cells.size())
        , width(cells.at(0).size())
        , visited(cells.size(), std::vector<bool>(cells.at(0).size(), false))
    {
    }

    bool canAchievePoint(Point from, Point to)
    {
        if (!isValidPoint(from) || !isValidPoint(to))
        {
            return false;
        }
        if (from == to)
        {
            return true;
        }
        if (isVisited(from))
        {
            return false;
        }
        markVisited(from);

        const size_t jumpLength = at(from);
        const Point left{ from.first - jumpLength, from.second };
        const Point right{ from.first + jumpLength, from.second };
        const Point top{ from.first, from.second - jumpLength };
        const Point bottom{ from.first, from.second + jumpLength };

        return canAchievePoint(left, to)
            || canAchievePoint(right, to)
            || canAchievePoint(top, to)
            || canAchievePoint(bottom, to);
    }

private:
    size_t at(Point p) const
    {
        return cells.at(p.second).at(p.first);
    }

    bool isVisited(Point p) const
    {
        return visited.at(p.second).at(p.first);
    }

    void markVisited(Point p)
    {
        visited.at(p.second).at(p.first) = true;
    }

    bool isValidPoint(Point p) const
    {
        return p.first < width && p.second < height;
    }

    const std::vector<std::vector<size_t>>& cells;
    const size_t width;
    const size_t height;
    std::vector<std::vector<bool>> visited;
};

bool canAchievePoint(const std::vector<std::vector<size_t>>& cells, Point from, Point to)
{
    Finder f(cells);
    return f.canAchievePoint(from, to);
}
