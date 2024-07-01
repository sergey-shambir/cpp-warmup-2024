#pragma once

#include <vector>
#include <optional>
#include "../04_flat_map/flat_map.h"

/**
 * Разреженный граф с последовательными индексами вершин
 */
class SparseGraph
{
public:
    explicit SparseGraph(size_t size);

    bool HasEdge(size_t fromVertex, size_t toVertex) const;

    std::optional<double> GetEdgeWeight(size_t fromVertex, size_t toVertex) const;

    size_t Size() const;

    void Resize(size_t vertexCount);

    void AddDirectedEdge(size_t fromVertex, size_t toVertex, double weight = 1.0);

    void AddUndirectedEdge(size_t fromVertex, size_t toVertex, double weight = 1.0);

private:
    using AdjacencyList = FlatMap<size_t, double>;

    void CheckVertexIndex(size_t maxVertexIndex);

    std::vector<AdjacencyList> verticies;
};
