#include "SparseGraph.h"
#include <format>
#include <stdexcept>

SparseGraph::SparseGraph(size_t vertexCount)
    : verticies(vertexCount)
{
}

bool SparseGraph::HasEdge(size_t fromVertex, size_t toVertex) const
{
    return verticies.at(fromVertex).Contains(toVertex);
}

std::optional<double> SparseGraph::GetEdgeWeight(size_t fromVertex, size_t toVertex) const
{
    return verticies.at(fromVertex).Get(toVertex);
}

size_t SparseGraph::VertexCount() const
{
    return verticies.size();
}

const SparseGraph::AdjacencyList& SparseGraph::GetAdjacencyList(size_t fromVertex) const
{
    return verticies.at(fromVertex);
}

void SparseGraph::AddDirectedEdge(size_t fromVertex, size_t toVertex, double weight)
{
    CheckVertexIndex((std::max)(fromVertex, toVertex));

    verticies[fromVertex].Add(toVertex, weight);
}

void SparseGraph::AddUndirectedEdge(size_t fromVertex, size_t toVertex, double weight)
{
    CheckVertexIndex((std::max)(fromVertex, toVertex));

    verticies[fromVertex].Add(toVertex, weight);
    verticies[toVertex].Add(fromVertex, weight);
}

void SparseGraph::CheckVertexIndex(size_t maxVertexIndex)
{
    if (verticies.size() <= maxVertexIndex)
    {
        throw std::invalid_argument(std::format("cannot add vertex with index {}: graph contains {} verticies", maxVertexIndex, verticies.size()));
    }
}
