#include "SparseGraphAlgorithms.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

using Catch::Matchers::Equals;

TEST_CASE("FindDistancesFromVertex works for graph with 4 verticies")
{
    SparseGraph graph(4);

    graph.AddUndirectedEdge(0, 3, 240.0);
    graph.AddUndirectedEdge(0, 2, 200.0);
    graph.AddUndirectedEdge(2, 3, 100.0);
    graph.AddUndirectedEdge(1, 3, 300.0);

    REQUIRE_THAT(FindDistancesFromVertex(graph, 0),
        Equals(std::vector<double>{ 0.0, 540.0, 200.0, 240.00 }));

    REQUIRE_THAT(FindDistancesFromVertex(graph, 1),
        Equals(std::vector<double>{ 540.0, 0.0, 400.0, 300.0 }));

    REQUIRE_THAT(FindDistancesFromVertex(graph, 2),
        Equals(std::vector<double>{ 200.0, 400.0, 0.0, 100.0 }));

    REQUIRE_THAT(FindDistancesFromVertex(graph, 3),
        Equals(std::vector<double>{ 240.0, 300.0, 100.0, 0.0 }));
}

TEST_CASE("FindDistancesFromVertex works for another graph with 4 verticies")
{
    SparseGraph graph(4);

    graph.AddUndirectedEdge(0, 3, 240.0);
    graph.AddUndirectedEdge(0, 2, 200.0);
    graph.AddUndirectedEdge(2, 3, 20.0);
    graph.AddUndirectedEdge(1, 3, 300.0);

    REQUIRE_THAT(FindDistancesFromVertex(graph, 0),
        Equals(std::vector<double>{ 0.0, 520.0, 200.0, 220.0 }));

    REQUIRE_THAT(FindDistancesFromVertex(graph, 1),
        Equals(std::vector<double>{ 520.0, 0.0, 320.0, 300.0 }));

    REQUIRE_THAT(FindDistancesFromVertex(graph, 2),
        Equals(std::vector<double>{ 200.0, 320.0, 0.0, 20.0 }));

    REQUIRE_THAT(FindDistancesFromVertex(graph, 3),
        Equals(std::vector<double>{ 220.0, 300.0, 20.0, 0.0 }));
}

TEST_CASE("FindDistancesFromVertex works for graph with one vertex")
{
    SparseGraph graph(1);
    REQUIRE_THAT(FindDistancesFromVertex(graph, 0),
        Equals(std::vector<double>{ 0.0 }));
}
