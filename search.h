#ifndef PROJETO2AED_SEARCH_H
#define PROJETO2AED_SEARCH_H
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include "Graph.h"
#include "userPreferences.h"

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
        if(neighbors[0].getWeight() == "AIRPORT") {
            neighbors.erase(neighbors.begin());
        }
        // Update distances to neighboring vertices
        for (const auto &edge : neighbors) {
                T neighborAirport = edge.getDest()->getInfo();
                int newDistance = distance[currentAirport] + 1; // Assuming equal weight for all edges

                // If a shorter path is found, update the distance
                if (newDistance < distance[neighborAirport] || distance[neighborAirport] == INT_MAX) {
                    distance[neighborAirport] = newDistance;
                    pq.push({newDistance, neighborAirport});
                }
        }
    }

    // Reconstruct all paths from endAirport to startAirport
    vector<vector<T>> allPaths;
    vector<T> currentPath;
    backtrackPaths(graph,distance, endAirport, startAirport, currentPath, allPaths);

    return allPaths;
}

template <class T>
void backtrackPaths(const Graph<T> &graph, const unordered_map<T, int> &distance, const T &start, const T &current, vector<T> &currentPath, vector<vector<T>> &allPaths) {
    if (current == start) {
        currentPath.push_back(current);
        allPaths.push_back(currentPath);
        currentPath.clear();
        return;
    }


    auto neighbors = graph.findVertex(current)->getAdj();
    if(neighbors[0].getWeight() == "AIRPORT") {
        neighbors.erase(neighbors.begin());
    }

    for (const auto &edge : neighbors) {
        currentPath.push_back(current);
        T neighborAirport = edge.getDest()->getInfo();
        auto tell = distance.at(neighborAirport);
        auto what = distance.at(start);
        if (distance.at(neighborAirport) > distance.at(start) || neighborAirport == start) {
            // Add the airline information between consecutive airports in the path
            currentPath.push_back(edge.getWeight());
            backtrackPaths(graph, distance, start, neighborAirport, currentPath, allPaths);
        } else {
            currentPath.clear();
        }
    }

}
template <class T>
string nameToCode(const Graph<T> &graph, string input) {
    vector<string> options;
    for(auto vertex: graph.getVertexSet()) {
        if(vertex->getAdj().empty()) {
            string id = getId(vertex->getInfo());
            if(getId(vertex->getInfo()) == "P") {
                string airportName = getAirportName(vertex->getInfo());
                transform(airportName.begin(), airportName.end(), airportName.begin(), ::tolower);
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if(airportName.find(input) != string::npos) {
                    options.push_back(vertex->getInfo().substr(2));
                }
            }
        }
    }
    // it slould display all the options in a menu so the user can select the option they want
    for(int i = 0; i < options.size(); i++) {
        cout << i + 1 << ". " << options[i] << endl;
    }
    int option;
    cin >> option;
    return getAirportCode(options[option-1]);
}

template <class T>
vector<string> cityToCode(const Graph<T> &graph, string input) {
    unordered_multimap<string, string> map;
    vector<string> options;
    for(auto vertex: graph.getVertexSet()) {
        if(vertex->getAdj().empty()) {
            string id = getId(vertex->getInfo());
            if(getId(vertex->getInfo()) == "P") {
                string airportCity = getCityName(vertex->getInfo());
                string airportCode = getAirportCode(vertex->getInfo());
                string country = getCountryName(vertex->getInfo());
                string option = airportCity + " - " + country;
                transform(airportCity.begin(), airportCity.end(), airportCity.begin(), ::tolower);
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if(airportCity.find(input) != string::npos) {
                    if(find(options.begin(), options.end(), option) == options.end()) {
                        options.push_back(option);
                    }
                    map.insert(pair<string, string> (option, airportCode));
                }
            }
        }
    }
    // it slould display all the options in a menu so the user can select the option they want
    for(int i = 0; i < options.size(); i++) {
        cout << i + 1 << ". " << options[i] << endl;
    }
    int option = 1;
    // cin >> option;
    vector<string> codes;
    for (auto & itr : map) {
        if(itr.first == options[option-1]) {
            codes.push_back(itr.second);
        }
    }
    return codes;
}

// ----------------------------------------------------------------
// ----------------------- FILTERING GRAPH ------------------------
// ----------------------------------------------------------------

template <class T>
Graph<T> filterGraph(const Graph<T> &originalGraph, const UserPreferences &userPreferences) {
    Graph<T> filteredGraph = originalGraph;

    // Remove airports based on avoidedAirports preference
    for (const auto &airport: userPreferences.avoidedAirports) {
        filteredGraph.removeVertex(airport);
    }

    // Remove edges based on avoidedAirlines preference
    if (!userPreferences.avoidedAirlines.empty()) {
        for (const auto &edge: originalGraph.getVertexSet()) {
            for (const auto &flight: edge->getAdj()) {
                if (std::find(userPreferences.avoidedAirlines.begin(), userPreferences.avoidedAirlines.end(),
                              flight.getWeight()) != userPreferences.avoidedAirlines.end()) {
                    // Remove the edge with the avoided airline
                    filteredGraph.removeEdgeByWeight(edge->getInfo(), flight.getDest()->getInfo(), flight.getWeight());
                }
            }
        }
    }

    // Remove airports based on avoidCountries preference
    if(!userPreferences.avoidedCountries.empty()) {
        for (auto vertex: originalGraph.getVertexSet()) {
            if (vertex->getAdj().empty()) {
                string id = getId(vertex->getInfo());
                if (getId(vertex->getInfo()) == "P") {
                    if (find(userPreferences.avoidedCountries.begin(), userPreferences.avoidedCountries.end(),
                             getCountryName(vertex->getInfo())) != userPreferences.avoidedCountries.end()) {
                        string airportCode = getAirportCode(vertex->getInfo());
                        filteredGraph.removeVertex(vertex->getInfo());
                        filteredGraph.removeVertex(airportCode);
                    }
                }
            }
        }
    }

    // Remove airports based on avoidCities preference
    if(!userPreferences.avoidedCities.empty()) {
        for (auto vertex: originalGraph.getVertexSet()) {
            if (vertex->getAdj().empty()) {
                string id = getId(vertex->getInfo());
                if (getId(vertex->getInfo()) == "P") {
                    if (find(userPreferences.avoidedCities.begin(), userPreferences.avoidedCities.end(),
                             getCityName(vertex->getInfo())) != userPreferences.avoidedCities.end()) {
                        string airportCode = getAirportCode(vertex->getInfo());
                        filteredGraph.removeVertex(vertex->getInfo());
                        filteredGraph.removeVertex(airportCode);
                    }
                }
            }
        }
    }

    // Remove airlines diferrent than the preferred ones
    if (!userPreferences.preferredAirlines.empty()) {
        // Create a list to store edges to be removed
        std::vector<std::tuple<T, T, std::string>> edgesToRemove;

        // Iterate over the filteredGraph
        for (const auto &vertex : filteredGraph.getVertexSet()) {
            if (!vertex->getAdj().empty()) {
                for (const auto &flight : vertex->getAdj()) {
                    if (flight.getWeight() != "AIRPORT" &&
                        std::find(userPreferences.preferredAirlines.begin(), userPreferences.preferredAirlines.end(),
                                  flight.getWeight()) == userPreferences.preferredAirlines.end()) {
                        // Add the edge to the list of edges to be removed
                        edgesToRemove.emplace_back(vertex->getInfo(), flight.getDest()->getInfo(), flight.getWeight());
                    }
                }
            }
        }

        // Remove the edges from the filteredGraph using the stored information
        for (const auto &edgeInfo : edgesToRemove) {
            filteredGraph.removeEdgeByWeight(std::get<0>(edgeInfo), std::get<1>(edgeInfo), std::get<2>(edgeInfo));
        }
    }

    // Remove airports different from the preferred ones
    if(!userPreferences.preferredAirports.empty()) {
        for (auto vertex: originalGraph.getVertexSet()) {
            if (vertex->getAdj().empty()) {
                string id = getId(vertex->getInfo());
                if (getId(vertex->getInfo()) == "P") {
                    if (find(userPreferences.preferredAirports.begin(), userPreferences.preferredAirports.end(),
                             getAirportCode(vertex->getInfo())) == userPreferences.preferredAirports.end()) {
                        string airportCode = getAirportCode(vertex->getInfo());
                        filteredGraph.removeVertex(vertex->getInfo());
                        filteredGraph.removeVertex(airportCode);
                    }
                }
            }
        }
    }

    // Remove airports different from the preferred countries
    if(!userPreferences.preferredCountries.empty()) {
        for (auto vertex: originalGraph.getVertexSet()) {
            if (vertex->getAdj().empty()) {
                string id = getId(vertex->getInfo());
                if (getId(vertex->getInfo()) == "P") {
                    if (find(userPreferences.preferredCountries.begin(), userPreferences.preferredCountries.end(),
                             getCountryName(vertex->getInfo())) == userPreferences.preferredCountries.end()) {
                        string airportCode = getAirportCode(vertex->getInfo());
                        filteredGraph.removeVertex(vertex->getInfo());
                        filteredGraph.removeVertex(airportCode);
                    }
                }
            }
        }
    }

    // Remove airports different from the preferred cities
    if(!userPreferences.preferredCities.empty()) {
        for (auto vertex: originalGraph.getVertexSet()) {
            if (vertex->getAdj().empty()) {
                string id = getId(vertex->getInfo());
                if (getId(vertex->getInfo()) == "P") {
                    if (find(userPreferences.preferredCities.begin(), userPreferences.preferredCities.end(),
                             getCityName(vertex->getInfo())) == userPreferences.preferredCities.end()) {
                        string airportCode = getAirportCode(vertex->getInfo());
                        filteredGraph.removeVertex(vertex->getInfo());
                        filteredGraph.removeVertex(airportCode);
                    }
                }
            }
        }
    }
    return filteredGraph;
}

#endif //PROJETO2AED_SEARCH_H