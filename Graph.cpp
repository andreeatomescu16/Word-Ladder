//
// Created by Andreea on 15.04.2024.
//

#include "Graph.h"
#include <iostream>
using std::vector;
#include <queue>
using std::queue;



template <typename T>
Graph<T>::Graph() {
    this->list_of_neighbours = std::vector<std::vector<T>>();
}

template <typename T>
Graph<T>::Graph(std::vector<std::vector<T>> vector) {
    this->list_of_neighbours = vector;
}

template <typename T>
const std::vector<std::vector<T>>& Graph<T>::getList() const {
    return this->list_of_neighbours;
}

template <typename T>
void Graph<T>::add_edge(T v1, T v2) {
    std::vector<T> vect;
    vect.push_back(v1);
    vect.push_back(v2);
    list_of_neighbours.push_back(vect);
}

template <typename T>
int Graph<T>::get_size() const {
    return list_of_neighbours.size();
}

template <typename T>
std::vector<T> Graph<T>::getNeighbours(T current) {
    std::vector<T> neighbours;
    for (int i = 0; i < list_of_neighbours.size(); i++)
        if (list_of_neighbours[i][0] == current) {
            bool ok = true;
            for (int j = 0; j < neighbours.size(); j++)
                if (neighbours[j] == list_of_neighbours[i][1])
                    ok = false;

            if (ok)
                neighbours.push_back(list_of_neighbours[i][1]);
        }
        else if (list_of_neighbours[i][1] == current) {
            bool ok = true;
            for (int j = 0; j < neighbours.size(); j++)
                if (neighbours[j] == list_of_neighbours[i][0])
                    ok = false;

            if (ok)
                neighbours.push_back(list_of_neighbours[i][0]);
        }
        return neighbours;
}