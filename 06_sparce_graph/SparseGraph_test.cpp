#include "SparseGraph.h"

#include <catch2/catch_test_macros.hpp>


TEST_CASE("SparseGraph can store verticies and edges")
{
    SparseGraph graph(4);

    graph.AddUndirectedEdge(0, 3, 240.0);
    graph.AddUndirectedEdge(0, 2, 200.0);
    graph.AddUndirectedEdge(2, 3, 100.0);
    graph.AddUndirectedEdge(1, 3, 300.0);

    REQUIRE(!graph.HasEdge(0, 1));
    REQUIRE(!graph.HasEdge(1, 1));

    REQUIRE(graph.HasEdge(0, 3));
    REQUIRE(graph.HasEdge(3, 0));
    REQUIRE(graph.HasEdge(0, 2));
    REQUIRE(graph.HasEdge(2, 0));
    REQUIRE(graph.HasEdge(1, 3));
    REQUIRE(graph.HasEdge(3, 1));
}
