#ifndef PROJETO2AED_STATISTICS_H
#define PROJETO2AED_STATISTICS_H
#include "extractFromDatabase.h"
#include "Graph.h"
#include <string>
#include <unordered_set>
#include <cmath>

string getCityName(string info) {
    string cityName;
    stringstream ss(info);
    getline(ss, cityName, ':');
    getline(ss, cityName, ',');
    getline(ss, cityName, ',');
    getline(ss, cityName, ',');
    return cityName;
}
string getCountryName(string info) {
    string countryName;
    stringstream ss(info);
    getline(ss, countryName, ':');
    getline(ss, countryName, ',');
    getline(ss, countryName, ',');
    getline(ss, countryName, ',');
    getline(ss, countryName, ',');
    return countryName;
}


namespace statistics {


/**
 * @brief Calculates the number of outgoing flights from a given airport in the graph.
 *
 * This function takes a graph representing airports and flights and a specific airport code.
 * It finds the vertex corresponding to the provided airport code in the graph and counts
 * the number of outgoing flights (edges) from that vertex.
 *
 * @param graph The graph representing airports and flights.
 * @param airportCode The code of the airport for which the outgoing flights are counted.
 * @return The number of outgoing flights from the specified airport.
 *
 * @pre The graph must be properly initialized.
 * @pre The provided airport code should exist in the graph.
 *
 */
    int numberOfFlightsOut(Graph<std::string> &graph, std::string airportCode) {
        int count = 0;
        auto vertex = graph.findVertex(airportCode);
        count += vertex->getAdj().size();
        return count;
    }

/**
 * @brief Calculates the number of unique airlines operating outgoing flights from a given airport in the graph.
 *
 * This function takes a graph representing airports and flights, and a specific airport code.
 * It finds the vertex corresponding to the provided airport code in the graph and counts
 * the number of unique airlines operating outgoing flights (edges) from that vertex.
 *
 * @param graph The graph representing airports and flights.
 * @param airportCode The code of the airport for which the number of unique airlines is counted.
 * @return The number of unique airlines operating outgoing flights from the specified airport.
 *
 * @pre The graph must be properly initialized.
 * @pre The provided airport code should exist in the graph.
 *
 */
    int numberOfAirlinesOut(Graph<std::string> &graph, std::string airportCode) {
        int count = 0;
        auto vertex = graph.findVertex(airportCode);
        string airlineCode;
        vector<string> airlines;
        for (int i = 1; i < vertex->getAdj().size(); i++) {
            airlineCode = vertex->getAdj()[i].getWeight();
            if (find(airlines.begin(), airlines.end(), airlineCode) == airlines.end()) {
                airlines.push_back(airlineCode);
                count++;
            }
        }
        return count;
    }

/**
 * @brief Calculates the total number of flights operated by a specific airline across all airports in the graph.
 *
 * This function takes a graph representing airports and flights, and a specific airline code.
 * It iterates through all vertices (airports) in the graph and counts the number of outgoing flights
 * (edges) operated by the specified airline from each airport.
 *
 * @param graph The graph representing airports and flights.
 * @param airlineCode The code of the airline for which the total number of flights is counted.
 * @return The total number of flights operated by the specified airline across all airports in the graph.
 *
 * @pre The graph must be properly initialized.
 * @pre The provided airline code should exist in the graph.
 */
    int numberOfFlightsPerAirline(Graph<std::string> &graph, std::string airlineCode) {
        int count = 0;
        for (auto vertex: graph.getVertexSet()) {
            for (int i = 1; i < vertex->getAdj().size(); i++) {
                if (vertex->getAdj()[i].getWeight() == airlineCode) {
                    count++;
                }
            }
        }
        return count;
    }

/**
 * @brief Calculates the total number of flights departing from airports located in a specific city in the graph.
 *
 * This function takes a graph representing airports and flights, and a specific city name.
 * It iterates through all vertices (airports) in the graph, identifies airports located in the specified city,
 * and counts the total number of outgoing flights (edges) from those airports.
 *
 * @param graph The graph representing airports and flights.
 * @param city The name of the city for which the total number of flights is counted.
 * @return The total number of flights departing from airports in the specified city in the graph.
 *
 * @pre The graph must be properly initialized.
 */
    int numberOfFlightsPerCity(Graph<std::string> &graph, std::string city) {
        int count = 0;
        for (auto vertex: graph.getVertexSet()) {
            if (vertex->getAdj().empty()) {
                string info = vertex->getInfo();
                string cityName;
                string airportCode;
                stringstream ss(info);
                getline(ss, cityName, ':');
                if (cityName == "P") {
                    getline(ss, airportCode, ',');
                    getline(ss, cityName, ',');
                    getline(ss, cityName, ',');
                    if (cityName == city) {
                        count += numberOfFlightsOut(graph, airportCode);
                    }
                }

            }

        }
        return count;
    }

/**
 * @brief Retrieves a list of unique destination airports reachable from a specified airport in the graph.
 *
 * This function takes a graph representing airports and flights and a specific airport code.
 * It finds the vertex corresponding to the provided airport code in the graph and generates a list
 * of unique destination airports that are reachable through outgoing flights from the specified airport.
 *
 * @param graph The graph representing airports and flights.
 * @param airportCode The code of the airport for which the list of destinations is retrieved.
 * @return A vector containing the unique airport codes of destinations reachable from the specified airport.
 *
 * @pre The graph must be properly initialized.
 * @pre The provided airport code should exist in the graph.
 */
    vector<string> listOfDestinations(Graph<std::string> &graph, std::string airportCode) {
        auto vertex = graph.findVertex(airportCode);
        vector<string> airports;
        for (int i = 1; i < vertex->getAdj().size(); i++) {
            if (find(airports.begin(), airports.end(), vertex->getAdj()[i].getDest()->getInfo()) == airports.end()) {
                airports.push_back(vertex->getAdj()[i].getDest()->getInfo());
            }
        }
        return airports;
    }

/**
 * @brief Calculates the number of unique destination airports in a given vector.
 *
 * This function takes a vector containing airport codes and calculates the total number of unique
 * destination airports represented in the vector.
 *
 * @param airports A vector containing airport codes representing destination airports.
 * @return The number of unique destination airports in the provided vector.
 *
 * @pre The vector must be non-empty and properly initialized.
 */
    int numberOfDestinationsAirports(vector<string> airports) {
        return (int) airports.size();
    }

/**
 * @brief Calculates the number of unique destination cities represented by a vector of airport codes in the graph.
 *
 * This function takes a graph representing airports and flights, and a vector containing airport codes.
 * It iterates through the provided vector, identifies airports located in cities, and counts the number of
 * unique destination cities represented by those airports in the graph.
 *
 * @param graph The graph representing airports and flights.
 * @param airports A vector containing airport codes for which the unique destination cities are counted.
 * @return The number of unique destination cities represented by the provided vector of airport codes.
 *
 * @pre The graph must be properly initialized.
 * @pre The vector of airport codes must be non-empty and properly initialized.
 */
    int numberOfDestinationsCities(Graph<std::string> &graph, vector<string> airports) {
        vector<string> cities;
        for (auto airport: airports) {
            auto vertex = graph.findVertex(airport);
            if (vertex->getAdj()[0].getWeight() == "AIRPORT") {
                string info = vertex->getAdj()[0].getDest()->getInfo();
                string cityName;
                stringstream ss(info);
                getline(ss, cityName, ':');
                getline(ss, cityName, ',');
                getline(ss, cityName, ',');
                getline(ss, cityName, ',');
                if (find(cities.begin(), cities.end(), cityName) == cities.end()) {
                    cities.push_back(cityName);
                }
            }
        }
        return (int) cities.size();
    }

/**
 * @brief Calculates the number of unique destination countries represented by a vector of airport codes in the graph.
 *
 * This function takes a graph representing airports and flights, and a vector containing airport codes.
 * It iterates through the provided vector, identifies airports located in countries, and counts the number of
 * unique destination countries represented by those airports in the graph.
 *
 * @param graph The graph representing airports and flights.
 * @param airports A vector containing airport codes for which the unique destination countries are counted.
 * @return The number of unique destination countries represented by the provided vector of airport codes.
 *
 * @pre The graph must be properly initialized.
 * @pre The vector of airport codes must be non-empty and properly initialized.
 */
    int numberOfDestinationsCountries(Graph<std::string> &graph, vector<string> airports) {
        vector<string> countries;
        for (auto airport: airports) {
            auto vertex = graph.findVertex(airport);
            if (vertex->getAdj()[0].getWeight() == "AIRPORT") {
                string info = vertex->getAdj()[0].getDest()->getInfo();
                string countryName;
                stringstream ss(info);
                getline(ss, countryName, ':');
                getline(ss, countryName, ',');
                getline(ss, countryName, ',');
                getline(ss, countryName, ',');
                getline(ss, countryName, ',');
                if (find(countries.begin(), countries.end(), countryName) == countries.end()) {
                    countries.push_back(countryName);
                }
            }
        }
        return (int) countries.size();
    }

    vector<vector<string>> vectorOfReachableAirports(Graph<std::string> &graph, std::string airportCode, int maxStops) {
        vector<vector<string>> airports;
        vector<string> airportsToVisit;
        vector<string> airportsVisited;
        airportsToVisit.push_back(airportCode);
        airports.push_back(airportsToVisit);
        for (int i = 0; i < maxStops; ++i) {
            airportsToVisit.clear();
            for (auto airport: airports[i]) {
                auto vertex = graph.findVertex(airport);
                for (int j = 1; j < vertex->getAdj().size(); ++j) {
                    if (find(airportsVisited.begin(), airportsVisited.end(),
                             vertex->getAdj()[j].getDest()->getInfo()) == airportsVisited.end()) {
                        if (find(airportsToVisit.begin(), airportsToVisit.end(),
                                 vertex->getAdj()[j].getDest()->getInfo()) == airportsToVisit.end()) {
                            airportsToVisit.push_back(vertex->getAdj()[j].getDest()->getInfo());
                            airportsVisited.push_back(vertex->getAdj()[j].getDest()->getInfo());
                        }
                    }
                }
            }
            airports.push_back(airportsToVisit);
        }
        return airports;
    }

    int numberOfReachableAirports(Graph<std::string> &graph, std::string airportCode, int maxStops) {
        auto airports = vectorOfReachableAirports(graph, airportCode, maxStops);
        int count = 0;
        for (auto airport: airports) {
            count += airport.size();
        }
        return count - 1;
    }

// create a function similar to the last one, but it should verify not by airport but by city
    int numberOfReacheableCities(Graph<std::string> &graph, std::string airportCode, int maxStops) {
        auto airports = vectorOfReachableAirports(graph, airportCode, maxStops);
        vector<string> cities;
        for (auto airport: airports) {
            for (auto airportCode: airport) {
                auto vertex = graph.findVertex(airportCode);
                if (vertex->getAdj()[0].getWeight() == "AIRPORT") {
                    string cityName = getCityName(vertex->getAdj()[0].getDest()->getInfo());
                    if (find(cities.begin(), cities.end(), cityName) == cities.end()) {
                        cities.push_back(cityName);
                    }
                }
            }
        }
        return (int) cities.size();
    }

// create a function similar to the last one, but it should verify not by airport but by Country
    int numberOfReacheableCountries(Graph<std::string> &graph, std::string airportCode, int maxStops) {
        auto airports = vectorOfReachableAirports(graph, airportCode, maxStops);
        vector<string> countries;
        for (auto airport: airports) {
            for (auto airportCode: airport) {
                auto vertex = graph.findVertex(airportCode);
                if (vertex->getAdj()[0].getWeight() == "AIRPORT") {
                    string countryName = getCountryName(vertex->getAdj()[0].getDest()->getInfo());
                    if (find(countries.begin(), countries.end(), countryName) == countries.end()) {
                        countries.push_back(countryName);
                    }
                }
            }
        }
        return (int) countries.size();
    }

    vector<std::string> maxTrip(Graph<std::string> &graph, std::string airportCode) {
        vector<std::string> trips;
        auto airports = vectorOfReachableAirports(graph, airportCode, 16);
        auto end = airports.size() - 1;
        while (airports[end].empty()) {
            end--;
        }
        for (auto airport: airports[end]) {
            trips.push_back(airportCode + " --> " + airport);
        }
        return trips;
    }

    vector<string> topAirports(Graph<std::string> &graph, int k) {
        pair<int, string> pairs;
        vector<pair<int, string > > top;
        for (auto vertex: graph.getVertexSet()) {
            if (!vertex->getAdj().empty()) {
                pairs.first = vertex->getAdj().size();
                pairs.second = vertex->getInfo();
                if (top.empty()) {
                    top.push_back(pairs);
                } else {
                    bool added = false;
                    for (int i = 0; i < top.size(); ++i) {
                        if (pairs.first > top[i].first) {
                            top.insert(top.begin() + i, pairs);
                            added = true;
                            break;
                        }
                    }
                    if (!added) {
                        top.push_back(pairs);
                    }
                }
            }
        }

        // now you should return a vector of pairs with only k elements
        vector<string> topK;
        for (int i = 0; i < k; ++i) {
            topK.push_back(top[i].second);
        }
        return topK;
    }

    int numFlights(Graph<string> mainGraph) {
        // this function returns the number of flights in the graph.
        int numFlights = mainGraph.getNumEdges();
        return numFlights;
    }

    double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
        const double R = 6371.0;
        double dLat = (lat2 * M_PI / 180.0) - (lat1 * M_PI / 180.0);
        double dLon = (lon2 * M_PI / 180.0) - (lon1 * M_PI / 180.0);

        double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
        double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

        double distance = R * c;

        return distance;
    }
}

#endif //PROJETO2AED_STATISTICS_H
