//
// Created by Andreea on 15.04.2024.
//

#ifndef EXTRA3_GRAPH_H
#define EXTRA3_GRAPH_H
#include <iostream>
#include <vector>

template <typename T>
class Graph {
public:
    Graph();
    Graph(std::vector<std::vector<T>> list);
    const std::vector<std::vector<T>>& getList() const;
    void add_edge(T v1, T v2);
    int get_size() const;
    std::vector<std::vector<T>>& getPointerList();
    std::vector<T> getNeighbours(T current);

private:
    std::vector<std::vector<T>> list_of_neighbours;
};

#include "Graph.cpp"
#endif // GRAPH_H