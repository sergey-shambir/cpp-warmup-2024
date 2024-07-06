#pragma once

#include "SparseGraph.h"

/**
 * Поиск расстояний от заданной вершины до всех вершин графа
 * Реализовано с помощью алгоритма Дейкстры
 */
std::vector<double> FindDistancesFromVertex(const SparseGraph& graph, size_t fromVertex);
