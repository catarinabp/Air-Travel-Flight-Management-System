#ifndef PROJETO2AED_SEARCH_H
#define PROJETO2AED_SEARCH_H
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include "Graph.h"
#include "UserPreferences.h"
#include "search.h"

/**
 * @brief Prints information corresponding to the provided airport code in the given graph.
 *
 * This function takes an airport code and looks up the corresponding vertex in the graph.
 * If the vertex has an outgoing edge of type "AIRPORT," it prints information about the destination airport,
 * including its name, city, and country.
 *
 * @param graph The graph containing airport information.
 * @param code The airport code for which information is to be printed.
 */
void codeToInfo(const Graph<string> &graph, string code) {
    auto vertex = graph.findVertex(code);
    if(vertex->getAdj()[0].getWeight() == "AIRPORT") {
        vertex->getAdj()[0].getDest()->getInfo();
        cout << code << "-> " << getAirportName(vertex->getAdj()[0].getDest()->getInfo()) << ", " << getCityName(vertex->getAdj()[0].getDest()->getInfo()) << ", " << getCountryName(vertex->getAdj()[0].getDest()->getInfo()) << endl;
    }
}

/**
 * @brief Takes user input for an airport code, validates its existence, and returns the corresponding airport information.
 *
 * This template function prompts the user to enter an airport code, checks if the entered code exists in the given graph,
 * and returns the airport information if valid. It performs a case-insensitive comparison and continues to ask for input
 * until a valid airport code is provided.
 *
 * @tparam T The type of data stored in the graph's vertices.
 * @param originalGraph The original graph containing airport information.
 *
 * @return The airport information (code, name, city) corresponding to the valid airport code entered by the user.
 */
template <class T>
string validOptionAirport(const Graph<T> &originalGraph) {
    string codeToTry;
    std::cout << endl;
    std::cout << "Please type the airport code: " << std::endl;
    std::cin >> codeToTry;
    for (auto vertex: originalGraph.getVertexSet()) {
        if (vertex->getAdj().empty()) {
            string id = getId(vertex->getInfo());
            if (getId(vertex->getInfo()) == "P") {
                transform(codeToTry.begin(), codeToTry.end(), codeToTry.begin(), ::toupper);
                if (getAirportCode(vertex->getInfo()) == codeToTry) {
                    cout << "Selected airport: " << getAirportCode(vertex->getInfo()) << ", " << getAirportName(vertex->getInfo()) << ", " << getCityName(vertex->getInfo()) << endl;
                    return getAirportCode(vertex->getInfo());
                }
            }
        }
    }
    cout << endl;
    cout << "That code doesn't exist! Please verify the spelling." << endl;
    return validOptionAirport(originalGraph);
}

/**
 * @brief Takes user input for an option within a specified range.
 *
 * This function prompts the user to enter an option within the specified range
 * [down + 1, up + 1]. It continues to ask for input until a valid integer within
 * the range is provided.
 *
 * @param down The lower bound of the allowed range (inclusive).
 * @param up   The upper bound of the allowed range (inclusive).
 *
 * @return The valid option entered by the user within the specified range.
 */
int validOptionInt(int down, int up) {
    int myNumber;

    // Loop until a valid integer is entered
    while (true) {
        std::cout << endl;
        std::cout << "Enter an option: ";

        if (std::cin >> myNumber && myNumber > down-1 && myNumber < up+1) {
            // Input was successful, break out of the loop
            break;
        } else {
            // Input failed, handle the error
            std::cout << "Invalid input. Please enter an option." << std::endl;

            // Clear the fail state
            std::cin.clear();

            // Discard the invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // You now have a valid integer in myNumber
    std::cout << "You entered: " << myNumber << std::endl;
    std::cout << endl;
    return myNumber;
}

/**
 * @brief Find the shortest paths from a start airport to an end airport in a graph.
 *
 * This function uses Dijkstra's algorithm to find the shortest paths from a start airport to an end airport
 * in the given graph. It returns a vector of vectors, where each inner vector represents a distinct shortest path.
 *
 * @tparam T The type of data stored in the graph vertices.
 * @param graph The input graph.
 * @param startAirport The code of the starting airport.
 * @param endAirport The code of the destination airport.
 * @return A vector of vectors containing the shortest paths.
 *
 * Example Usage:
 * @code
 *    Graph<string> flightGraph;
 *    // Populate flightGraph...
 *    string startAirport = "OPO";
 *    string endAirport = "JFK";
 *    auto paths = findShortestPath(flightGraph, startAirport, endAirport);
 *    // Use paths for further processing...
 * @endcode
 */
template <class T>
vector<vector<T>> findShortestPath(const Graph<T> &graph, const T &startAirport, const T &endAirport) {
    vector<vector<T>> allPaths;
    vector<T> currentPath;

    if(endAirport != startAirport) {
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
            if(!graph.findVertex(currentAirport)->getAdj().empty()) {
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
        }

        // Reconstruct all paths from endAirport to startAirport
        backtrackPaths(graph,distance, endAirport, startAirport, currentPath, allPaths);
    }

    return allPaths;
}

/**
 * @brief Backtrack and find paths from the current airport to the destination in a graph.
 *
 * This function recursively backtracks and finds paths from the current airport to the destination
 * in the given graph. It considers the distances provided and adds information about airlines between
 * consecutive airports in the path. The results are stored in the `allPaths` vector.
 *
 * @tparam T The type of data stored in the graph vertices.
 * @param graph The input graph.
 * @param distance A map containing distances from the start airport to each vertex.
 * @param end The destination airport.
 * @param current The current airport in the path.
 * @param currentPath The current path being constructed.
 * @param allPaths Vector to store all the paths found.
 * @param initialSize The initial size of the current path vector (default is 2).
 *
 * Example Usage:
 * @code
 *    Graph<string> flightGraph;
 *    // Populate flightGraph...
 *    string startAirport = "OPO";
 *    string endAirport = "JFK";
 *    unordered_map<string, int> distances; // Populate distances map...
 *    vector<vector<string>> paths;
 *    vector<string> currentPath;
 *    backtrackPaths(flightGraph, distances, endAirport, startAirport, currentPath, paths);
 *    // Use paths for further processing...
 * @endcode
 */
template <class T>
void backtrackPaths(const Graph<T> &graph, const unordered_map<T, int> &distance, const T &end, const T &current, vector<T> &currentPath, vector<vector<T>> &allPaths, size_t initialSize = 2) {
    auto meu = distance.at(end);
    if(distance.at(end) != INT_MAX) {
        if (current == end) {
            currentPath.push_back(current);
            allPaths.push_back(currentPath);
            currentPath.resize(initialSize);
            return;
        }
        initialSize = currentPath.size();

        auto neighbors = graph.findVertex(current)->getAdj();
        if(neighbors[0].getWeight() == "AIRPORT") {
            neighbors.erase(neighbors.begin());
        }

        for (const auto &edge : neighbors) {
            currentPath.push_back(current);
            T neighborAirport = edge.getDest()->getInfo();
            if(find(currentPath.begin(), currentPath.end(), neighborAirport) == currentPath.end()) {
                auto lessThanCurrent = (int) currentPath.size() / 2 + 1 < distance.at(end);
                // auto lessDifferentThatSource = distance.at(neighborAirport) + distance.at(current) < distance.at(end) && distance.at(neighborAirport) != 0;
                auto sameAsEnd = neighborAirport == end;
                auto higherOnlyIfEnd = (distance.at(neighborAirport) + distance.at(current) > distance.at(end) && neighborAirport == end);

                if (lessThanCurrent || sameAsEnd || higherOnlyIfEnd) {
                    // Add the airline information between consecutive airports in the path
                    currentPath.push_back(edge.getWeight());
                    backtrackPaths(graph, distance, end, neighborAirport, currentPath, allPaths, initialSize);
                } else {
                    currentPath.resize(initialSize);
                }
            }

        }
        if(initialSize >= 2) {
            currentPath.resize(initialSize-2);
        }
    }
}
/**
 * @brief Convert an airport name to its corresponding code.
 *
 * This function searches for airports in the given graph whose names match the input string.
 * It displays the matching options and allows the user to select the desired option by entering
 * a corresponding number. The function then returns the airport code for the selected option.
 *
 * @tparam T The type of data stored in the graph vertices.
 * @param graph The input graph.
 * @param input The input string representing the airport name.
 * @return The airport code corresponding to the selected option.
 *
 * Example Usage:
 * @code
 *    Graph<string> flightGraph;
 *    // Populate flightGraph...
 *    string userInput = "Los Angeles";
 *    string airportCode = nameToCode(flightGraph, userInput);
 *    // Use airportCode for further processing...
 * @endcode
 */
template <class T>
string nameToCode(const Graph<T> &graph, string input) {
    bool stop = false;
    vector<string> options;
    for(auto vertex: graph.getVertexSet()) {
        if(vertex->getAdj().empty()) {
            string id = getId(vertex->getInfo());
            if(getId(vertex->getInfo()) == "P") {
                string airportName = getAirportName(vertex->getInfo());
                transform(airportName.begin(), airportName.end(), airportName.begin(), ::tolower);
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if(airportName.find(input) != string::npos) {
                    options.push_back(vertex->getInfo());
                }
            }
        }
    }
    if(options.empty()) {
        stop = true;
        cout << "There is no airport with this name. Try again." << endl;
        while(stop) {
            std::cout << "Please type the airport name: " << std::endl;
            string source;
            std::getline(std::cin, source);
            return nameToCode(graph, source);
        }
    }
    // it should display all the options in a menu so the user can select the option they want
    int option = 1;
    if(options.size() > 1) {
        cout << "Choose the option you want: " << endl;
        for(int i = 0; i < options.size(); i++) {
            cout << i + 1 << ". " << options[i].substr(2) << endl;
        }
        option = validOptionInt(1, (int) options.size());
    }

    return getAirportCode(options[option-1]);
}

/**
 * @brief Convert a city name to corresponding airport codes.
 *
 * This function searches for airports in the given graph whose cities match the input string.
 * It displays the matching options and allows the user to select the desired option by entering
 * a corresponding number. The function then returns a vector of airport codes corresponding to the selected option.
 *
 * @tparam T The type of data stored in the graph vertices.
 * @param graph The input graph.
 * @param input The input string representing the city name.
 * @return A vector of airport codes corresponding to the selected option.
 *
 * Example Usage:
 * @code
 *    Graph<string> flightGraph;
 *    // Populate flightGraph...
 *    string userInput = "Los Angeles";
 *    vector<string> airportCodes = cityToCode(flightGraph, userInput);
 *    // Use airportCodes for further processing...
 * @endcode
 */
template <class T>
vector<string> cityToCode(const Graph<T> &graph, string input) {
    bool stop = false;
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
    if(options.empty()) {
        stop = true;
        cout << "There is no city with this name. Try again." << endl;
        while(stop) {
            std::cout << "Please type the city's name: " << std::endl;
            string city;
            std::getline(std::cin, city);
            return cityToCode(graph, city);
        }
    }
    int option = 1;
    if(options.size() > 1) {
        cout << "Choose the option you want: " << endl;
        for(int i = 0; i < options.size(); i++) {
            cout << i + 1 << ". " << options[i].substr(2) << endl;
        }
        option = validOptionInt(1, (int) options.size());
    }

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

/**
 * @brief Filter a graph based on user preferences.
 *
 * This function takes an original graph and applies user preferences to filter out vertices and edges.
 * It removes airports, edges with avoided airlines, airports from avoided countries and cities,
 * edges with non-preferred airlines, and airports not from preferred countries or cities.
 *
 * @tparam T The type of data stored in the graph vertices.
 * @param originalGraph The original input graph.
 * @param userPreferences The user preferences specifying filtering criteria.
 * @return A new graph containing only the vertices and edges that satisfy the user preferences.
 *
 * Example Usage:
 * @code
 *    Graph<string> originalGraph;
 *    // Populate originalGraph...
 *    UserPreferences preferences;
 *    // Set user preferences...
 *    Graph<string> filteredGraph = filterGraph(originalGraph, preferences);
 *    // Use filteredGraph for further processing...
 * @endcode
 */
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

    // Remove airlines different from the preferred ones
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