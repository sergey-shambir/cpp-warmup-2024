#include "SparseGraphAlgorithms.h"
#include <limits>
#include <queue>

namespace
{

// Note: the order in this pair is important for comparison.
using DistanceTo = std::pair<double, size_t>;

using MinDistanceToQueue = std::priority_queue<DistanceTo, std::vector<DistanceTo>, std::greater<DistanceTo>>;

constexpr double INFINITY_WEIGHT = std::numeric_limits<double>::infinity();

class DijkstraAlgorithmState
{
public:
    explicit DijkstraAlgorithmState(size_t size)
        : distances(size, INFINITY_WEIGHT)
    {
    }

    double Distance(size_t vertex) const
    {
        return distances[vertex];
    }

    void UpdateDistance(size_t vertex, double distance)
    {
        distances[vertex] = distance;
        queue.push({ distance, vertex });
    }

    bool IsFinished() const
    {
        return queue.empty();
    }

    DistanceTo PopMinDistance()
    {
        const auto result = queue.top();
        queue.pop();
        return result;
    }

    std::vector<double>&& TakeResults()
    {
        return std::move(distances);
    }

private:
    MinDistanceToQueue queue;
    std::vector<double> distances;
};
} // namespace

std::vector<double> FindDistancesFromVertex(const SparseGraph& graph, size_t fromVertex)
{
    DijkstraAlgorithmState state(graph.VertexCount());

    state.UpdateDistance(fromVertex, 0.0);

    while (!state.IsFinished())
    {
        const auto [queuedDistance, vertexIndex] = state.PopMinDistance();
        const double currentDistance = state.Distance(vertexIndex);

        if (queuedDistance > currentDistance)
        {
            continue; // Ignore outdated distances from queue.
        }

        for (auto [toVertex, weight] : graph.GetAdjacencyList(vertexIndex))
        {
            const double newDistance = currentDistance + weight;
            if (newDistance < state.Distance(toVertex))
            {
                state.UpdateDistance(toVertex, newDistance);
            }
        }
    }

    return state.TakeResults();
}
