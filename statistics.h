#ifndef PROJETO2AED_STATISTICS_H
#define PROJETO2AED_STATISTICS_H
#include "extractFromDatabase.h"
#include "Graph.h"
#include <string>

/**
 * @brief Extracts and returns the city name from the provided information string.
 *
 * This function parses the input information string to extract the city name.
 * The information string is expected to have a specific format where the city
 * name is delimited by commas.
 *
 * @param info The information string containing details, including the city name.
 * @return The extracted city name.
 *
 * @note The input information string should have the format:
 *       "field1:value,field2:value,field3:value,cityName:value,field4:value"
 */
string getCityName(const string& info) {
    string cityName;
    stringstream ss(info);
    // Extract city name (assuming it is the fourth field separated by commas)
    getline(ss, cityName, ':');
    getline(ss, cityName, ',');
    getline(ss, cityName, ',');
    getline(ss, cityName, ',');
    return cityName;
}

/**
 * @brief Extracts and returns the country name from the provided information string.
 *
 * This function assumes a specific format where the country name is the fifth
 * field separated by commas in the input information string.
 *
 * @param info The information string containing details, including the country name.
 * @return The extracted country name.
 *
 * @note The input information string should have the format: "field1:value,field2:value,field3:value,cityName:value,countryName:value,field4:value"
 */
string getCountryName(const string& info) {
    string countryName;
    stringstream ss(info);
    // Extract country name (assuming it is the fifth field separated by commas)
    getline(ss, countryName, ':');
    getline(ss, countryName, ',');
    getline(ss, countryName, ',');
    getline(ss, countryName, ',');
    getline(ss, countryName, ',');
    return countryName;
}

/**
 * @brief Extracts and returns the airport name from the provided information string.
 *
 * This function assumes a specific format where the airport name is the third
 * field separated by commas in the input information string.
 *
 * @param info The information string containing details, including the airport name.
 * @return The extracted airport name.
 *
 * @note The input information string should have the format: "field1:value,field2:value,airportName:value,field3:value,field4:value"
 *
 */
string getAirportName(const string& info) {
    string airportName;
    stringstream ss(info);
    // Extract airport name (assuming it is the third field separated by commas)
    getline(ss, airportName, ':');
    getline(ss, airportName, ',');
    getline(ss, airportName, ',');
    return airportName;
}

/**
 * @brief Extracts and returns the airport code from the provided information string.
 *
 * This function assumes a specific format where the airport code is the second
 * field separated by commas in the input information string.
 *
 * @param info The information string containing details, including the airport code.
 * @return The extracted airport code.
 *
 * @note The input information string should have the format: "field1:value,airportCode:value,field2:value,field3:value,field4:value"
 */
string getAirportCode(const string& info) {
    string airportCode;
    stringstream ss(info);
    // Extract airport code (assuming it is the second field separated by commas)
    getline(ss, airportCode, ':');
    getline(ss, airportCode, ',');
    return airportCode;
}

/**
 * @brief Extracts and returns the identifier from the provided information string.
 *
 * This function assumes a specific format where the identifier is the first
 * field separated by a colon in the input information string.
 *
 * @param info The information string containing details, including the identifier.
 * @return The extracted identifier.
 *
 * @note The input information string should have the format: "id:value,field1:value,field2:value,field3:value,field4:value"
 */
string getId(const string& info) {
    string id;
    stringstream ss(info);
    // Extract identifier (assuming it is the first field separated by a colon)
    getline(ss, id, ':');
    return id;
}

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
int numberOfFlightsOut(Graph<std::string> &graph, const std::string& airportCode) {
    int count = 0;
    auto vertex = graph.findVertex(airportCode);
    count += (int) vertex->getAdj().size();
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
int numberOfAirlinesOut(Graph<std::string> &graph, const std::string& airportCode) {
    int count = 0;
    auto vertex = graph.findVertex(airportCode);
    string airlineCode;
    vector<string> airlines;
    for(int i = 1; i < vertex->getAdj().size(); i++){
        airlineCode = vertex->getAdj()[i].getWeight();
        if(find(airlines.begin(), airlines.end(), airlineCode) == airlines.end()){
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
int numberOfFlightsPerAirline(Graph<std::string> &graph, const std::string& airlineCode) {
    int count = 0;
    for(auto vertex : graph.getVertexSet()){
        for(int i = 1; i < vertex->getAdj().size(); i++){
            if(vertex->getAdj()[i].getWeight() == airlineCode){
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
int numberOfFlightsPerCity(Graph<std::string> &graph, const std::string& city) {
    int count = 0;
    for(auto vertex : graph.getVertexSet()){
        if(vertex->getAdj().empty()){
            string info = vertex->getInfo();
            string cityName;
            string airportCode;
            stringstream ss(info);
            getline(ss, cityName, ':');
            if(cityName == "P") {
                getline(ss, airportCode, ',');
                getline(ss, cityName, ',');
                getline(ss, cityName, ',');
                if(cityName == city){
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
vector<string> listOfDestinations(Graph<std::string> &graph, const std::string& airportCode) {
    auto vertex = graph.findVertex(airportCode);
    vector<string> airports;
    for(int i = 1; i < vertex->getAdj().size(); i++){
        if(find(airports.begin(), airports.end(), vertex->getAdj()[i].getDest()->getInfo()) == airports.end()){
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
int numberOfDestinationsAirports(const vector<string>& airports) {
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
int numberOfDestinationsCities(Graph<std::string> &graph, const vector<string>& airports) {
    vector<string> cities;
    for(const auto& airport: airports) {
        auto vertex = graph.findVertex(airport);
        if(vertex->getAdj()[0].getWeight() == "AIRPORT"){
            string info = vertex->getAdj()[0].getDest()->getInfo();
            string cityName;
            stringstream ss(info);
            getline(ss, cityName, ':');
            getline(ss, cityName, ',');
            getline(ss, cityName, ',');
            getline(ss, cityName, ',');
            if(find(cities.begin(), cities.end(), cityName) == cities.end()){
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
int numberOfDestinationsCountries(Graph<std::string> &graph, const vector<string>& airports) {
        vector<string> countries;
        for(const auto& airport: airports) {
            auto vertex = graph.findVertex(airport);
            if(vertex->getAdj()[0].getWeight() == "AIRPORT"){
                string info = vertex->getAdj()[0].getDest()->getInfo();
                string countryName;
                stringstream ss(info);
                getline(ss, countryName, ':');
                getline(ss, countryName, ',');
                getline(ss, countryName, ',');
                getline(ss, countryName, ',');
                getline(ss, countryName, ',');
                if(find(countries.begin(), countries.end(), countryName) == countries.end()){
                    countries.push_back(countryName);
                }
            }
        }
        return (int) countries.size();
}

/**
 * @brief Finds and returns a vector of vectors containing reachable airports within a specified maximum number of stops.
 *
 * This function performs a breadth-first search to find airports reachable from the provided airport code
 * within the given maximum number of stops. The result is a vector of vectors, where each vector represents
 * the airports reachable within a specific number of stops.
 *
 * @param graph The graph representing the airport connections.
 * @param airportCode The code of the starting airport.
 * @param maxStops The maximum number of stops allowed in the search.
 * @return A vector of vectors containing reachable airports at each level of stops.
 *
 * @note The input graph should represent airport connections using vertices and edges.
 */
vector<vector<string>> vectorOfReachableAirports(Graph<std::string> &graph, const std::string& airportCode, int maxStops){
    vector<vector<string>> airports;
    vector<string> airportsToVisit;
    vector<string> airportsVisited;
    airportsToVisit.push_back(airportCode);
    airports.push_back(airportsToVisit);
    for(int i = 0; i < maxStops; ++i){
        airportsToVisit.clear();
        for(const auto& airport: airports[i]){
            auto vertex = graph.findVertex(airport);
            for(int j = 1; j < vertex->getAdj().size(); ++j){
                if(find(airportsVisited.begin(), airportsVisited.end(), vertex->getAdj()[j].getDest()->getInfo()) == airportsVisited.end()){
                    if(find(airportsToVisit.begin(), airportsToVisit.end(), vertex->getAdj()[j].getDest()->getInfo()) == airportsToVisit.end()){
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

/**
 * @brief Calculates the total number of reachable airports within a specified maximum number of stops.
 *
 * This function uses the vectorOfReachableAirports function to find airports reachable from the provided airport code
 * within the given maximum number of stops. The total count of reachable airports is then calculated and returned.
 *
 * @param graph The graph representing the airport connections.
 * @param airportCode The code of the starting airport.
 * @param maxStops The maximum number of stops allowed in the search.
 * @return The total number of reachable airports within the specified number of stops.
 *
 * @note The input graph should represent airport connections using vertices and edges.
 *
 * Example Usage:
 * @code
 *    Graph<std::string> airportGraph;  // Assume a properly initialized graph
 *    std::string startAirportCode = "JFK";
 *    int maxStopsAllowed = 3;
 *    int totalReachableAirports = numberOfReachableAirports(airportGraph, startAirportCode, maxStopsAllowed);
 *    // totalReachableAirports now contains the count of reachable airports within the specified stops
 * @endcode
 */
int numberOfReachableAirports(Graph<std::string> &graph, const std::string& airportCode, int maxStops) {
    auto airports = vectorOfReachableAirports(graph, airportCode, maxStops);
    int count = 0;
    for(const auto& airport: airports){
        count += (int) airport.size();
    }
    return count-1;
}

/**
 * @brief Calculates the total number of reachable cities within a specified maximum number of stops.
 *
 * This function uses the vectorOfReachableAirports function to find airports reachable from the provided airport code
 * within the given maximum number of stops. It then extracts the city names associated with those airports and
 * calculates the total count of unique reachable cities.
 *
 * @param graph The graph representing the airport connections.
 * @param airportCode The code of the starting airport.
 * @param maxStops The maximum number of stops allowed in the search.
 * @return The total number of unique reachable cities within the specified number of stops.
 *
 * @note The input graph should represent airport connections using vertices and edges, where the first edge weight
 * represents the airport information.
 *
 * Example Usage:
 * @code
 *    Graph<std::string> airportGraph;  // Assume a properly initialized graph
 *    std::string startAirportCode = "JFK";
 *    int maxStopsAllowed = 3;
 *    int totalReachableCities = numberOfReachableCities(airportGraph, startAirportCode, maxStopsAllowed);
 *    // totalReachableCities now contains the count of unique reachable cities within the specified stops
 * @endcode
 */
int numberOfReachableCities(Graph<std::string> &graph, const std::string& airportCode, int maxStops) {
    auto airports = vectorOfReachableAirports(graph, airportCode, maxStops);
    vector<string> cities;
    for(const auto& airport: airports){
        for(const auto& airportCoded: airport){
            auto vertex = graph.findVertex(airportCoded);
            if(vertex->getAdj()[0].getWeight() == "AIRPORT"){
                string cityName = getCityName(vertex->getAdj()[0].getDest()->getInfo()) ;
                if(find(cities.begin(), cities.end(), cityName) == cities.end()){
                    cities.push_back(cityName);
                }
            }
        }
    }
    return (int) cities.size();
}
/**
 * @brief Calculates the total number of reachable countries within a specified maximum number of stops.
 *
 * This function uses the vectorOfReachableAirports function to find airports reachable from the provided airport code
 * within the given maximum number of stops. It then extracts the country names associated with those airports and
 * calculates the total count of unique reachable countries.
 *
 * @param graph The graph representing the airport connections.
 * @param airportCode The code of the starting airport.
 * @param maxStops The maximum number of stops allowed in the search.
 * @return The total number of unique reachable countries within the specified number of stops.
 *
 * @note The input graph should represent airport connections using vertices and edges, where the first edge weight
 * represents the airport information.
 *
 * Example Usage:
 * @code
 *    Graph<std::string> airportGraph;  // Assume a properly initialized graph
 *    std::string startAirportCode = "JFK";
 *    int maxStopsAllowed = 3;
 *    int totalReachableCountries = numberOfReachableCountries(airportGraph, startAirportCode, maxStopsAllowed);
 *    // totalReachableCountries now contains the count of unique reachable countries within the specified stops
 * @endcode
 */
int numberOfReachableCountries(Graph<std::string> &graph, const std::string& airportCode, int maxStops) {
    auto airports = vectorOfReachableAirports(graph, airportCode, maxStops);
    vector<string> countries;
    for(const auto& airport: airports){
        for(const auto& airportCoded: airport){
            auto vertex = graph.findVertex(airportCoded);
            if(vertex->getAdj()[0].getWeight() == "AIRPORT"){
                string countryName = getCountryName(vertex->getAdj()[0].getDest()->getInfo());
                if(find(countries.begin(), countries.end(), countryName) == countries.end()){
                    countries.push_back(countryName);
                }
            }
        }
    }
    return (int) countries.size();
}

/**
 * @brief Finds the maximum trip from the provided airport code within a specified maximum number of stops.
 *
 * This function uses the vectorOfReachableAirports function to find airports reachable from the provided airport code
 * within the given maximum number of stops. It then identifies the last non-empty level in the reachability hierarchy
 * and constructs trips from the starting airport code to each airport at that level.
 *
 * @param graph The graph representing the airport connections.
 * @param airportCode The code of the starting airport.
 * @return A vector of strings representing the trips from the provided airport code to each airport at the last reachable level.
 *
 * @note The input graph should represent airport connections using vertices and edges, where the first edge weight
 * represents the airport information.
 *
 * Example Usage:
 * @code
 *    Graph<std::string> airportGraph;  // Assume a properly initialized graph
 *    std::string startAirportCode = "JFK";
 *    std::vector<std::string> maxTrips = maxTrip(airportGraph, startAirportCode);
 *    // maxTrips now contains trips from the provided airport code to each airport at the last reachable level
 * @endcode
 */
vector<std::string> maxTrip(Graph<std::string> &graph, const std::string& airportCode){
    vector<std::string> trips;
    auto airports = vectorOfReachableAirports(graph, airportCode, 16);
    auto end = airports.size()-1;
    while(airports[end].empty()){
        end--;
    }
    for(const auto& airport : airports[end]) {
        trips.push_back(airportCode + " --> " + airport);
    }
    return trips;
}

/**
 * @brief Finds the top K airports based on the number of outgoing flights.
 *
 * This function calculates the number of outgoing flights for each airport in the provided graph
 * and then identifies the top K airports with the highest number of outgoing flights.
 *
 * @param graph The graph representing airport connections.
 * @param k The number of top airports to retrieve.
 * @return A vector of strings representing the top K airports based on the number of outgoing flights.
 *
 * @note The input graph should represent airport connections using vertices and edges, where the first edge weight
 * represents the airport information.
 *
 * Example Usage:
 * @code
 *    Graph<std::string> airportGraph;  // Assume a properly initialized graph
 *    int k = 5;  // Number of top airports to retrieve
 *    std::vector<std::string> topAirportCodes = topAirports(airportGraph, k);
 *    // topAirportCodes now contains the codes of the top K airports based on outgoing flights
 * @endcode
 */
vector<string> topAirports(Graph<std::string> &graph, int k) {
    pair<int, string> pairs;
    vector<pair<int, string>> top;
    for(auto vertex: graph.getVertexSet()) {
        if(!vertex->getAdj().empty()) {
            pairs.first = (int) vertex->getAdj().size();
            pairs.second = vertex->getInfo();
            if(top.empty()){
                top.push_back(pairs);
            }
            else{
                bool added = false;
                for(int i = 0; i < top.size(); ++i){
                    if(pairs.first > top[i].first){
                        top.insert(top.begin()+i, pairs);
                        added = true;
                        break;
                    }
                }
                if(!added){
                    top.push_back(pairs);
                }
            }
        }
    }
    // now you should return a vector of pairs with only k elements
    vector<string> topK;
    for(int i = 0; i < k; ++i){
        topK.push_back(top[i].second);
    }
    return topK;
}

#endif //PROJETO2AED_STATISTICS_H
