#ifndef PROJETO2AED_SEARCH_H
#define PROJETO2AED_SEARCH_H
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include "Graph.h"

template <class T>
vector<vector<T>> findShortestPath(const Graph<T> &graph, const T &startAirport, const T &endAirport) {
    // Map to store distances from startAirport to each vertex
    unordered_map<T, int> distance;

    // Priority queue to store vertices and their distances
    priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> pq;

    // Initialize distances
    for (const auto &vertex : graph.getVertexSet()) {
        if(!vertex->getAdj().empty()) {
            if(vertex->getAdj()[0].getWeight() == "AIRPORT") {
                distance[vertex->getInfo()] = INT_MAX;
            }
        }
    }

    // Set distance for the startAirport to 0
    distance[startAirport] = 0;

    // Insert startAirport into the priority queue
    pq.push({0, startAirport});

    // Dijkstra's algorithm
    while (!pq.empty()) {
        // Extract the vertex with the smallest distance
        T currentAirport = pq.top().second;
        pq.pop();

        // Get neighboring vertices of the currentAirport
        auto neighbors = graph.findVertex(currentAirport)->getAdj();
        neighbors.erase(neighbors.begin());

        // Update distances to neighboring vertices
        for (const auto &edge : neighbors) {
            T neighborAirport = edge.getDest()->getInfo();
            int newDistance = distance[currentAirport] + 1; // Assuming equal weight for all edges

            // If a shorter path is found, update the distance
            if (newDistance < distance[neighborAirport]) {
                distance[neighborAirport] = newDistance;
                pq.push({newDistance, neighborAirport});
            }
        }
    }

    // Reconstruct all paths from endAirport to startAirport
    vector<vector<T>> allPaths;
    vector<T> currentPath;
    backtrackPaths(graph,distance, startAirport, endAirport, currentPath, allPaths);

    //Remove the repeated paths
    for (int i = 0; i < allPaths.size(); i++) {
        for (int j = i + 1; j < allPaths.size(); j++) {
            if (allPaths[i] == allPaths[j]) {
                allPaths.erase(allPaths.begin() + j);
                j--;
            }
        }
    }

    return allPaths;
}

template <class T>
void backtrackPaths(const Graph<T> &graph, const unordered_map<T, int> &distance, const T &start, const T &current, vector<T> &currentPath, vector<vector<T>> &allPaths) {
    if (current == start) {
        currentPath.push_back(current);
        allPaths.push_back(currentPath);
        currentPath.pop_back();
        return;
    }

    currentPath.push_back(current);

    auto neighbors = graph.findVertex(current)->getAdj();
    neighbors.erase(neighbors.begin());

    for (const auto &edge : neighbors) {
        T neighborAirport = edge.getDest()->getInfo();
        if (distance.at(neighborAirport) + 1 == distance.at(current)) {
            backtrackPaths(graph,distance, start, neighborAirport, currentPath, allPaths);
        }
    }

    currentPath.pop_back();
}

#endif //PROJETO2AED_SEARCH_H
