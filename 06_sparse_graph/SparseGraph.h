#pragma once

#include "../04_flat_map/flat_map.h"
#include <optional>
#include <vector>

/**
 * Разреженный граф с последовательными индексами вершин
 */
class SparseGraph
{
public:
    using AdjacencyList = FlatMap<size_t, double>;

    explicit SparseGraph(size_t vertexCount);

    bool HasEdge(size_t fromVertex, size_t toVertex) const;

    std::optional<double> GetEdgeWeight(size_t fromVertex, size_t toVertex) const;

    size_t VertexCount() const;

    const AdjacencyList& GetAdjacencyList(size_t fromVertex) const;

    void AddDirectedEdge(size_t fromVertex, size_t toVertex, double weight = 1.0);

    void AddUndirectedEdge(size_t fromVertex, size_t toVertex, double weight = 1.0);

private:
    void CheckVertexIndex(size_t maxVertexIndex);

    std::vector<AdjacencyList> verticies;
};
