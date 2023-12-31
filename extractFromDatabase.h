#ifndef PROJETO2AED_EXTRACTFROMDATABASE_H
#define PROJETO2AED_EXTRACTFROMDATABASE_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"

using namespace std;

/**
 * @brief Extracts airport, airline, and flight information from CSV files to create a graph.
 *
 * This function reads airport, airline, and flight information from CSV files and constructs a graph
 * representing the connections between airports and airlines.
 *
 * @param numberOfAirports Reference to store the total number of airports extracted.
 * @param numberOfAirlines Reference to store the total number of airlines extracted.
 * @param numberOfFlights Reference to store the total number of flights extracted.
 * @return A graph representing airport and airline connections.
 *
 * @note Assumes the existence of three CSV files: airports.csv, flights.csv, and airlines.csv.
 * The format of these CSV files must be suitable for parsing (comma-separated values).
 *
 * Example Usage:
 * @code
 *    int numAirports, numAirlines, numFlights;
 *    Graph<std::string> airportGraph = extractFromDatabase(numAirports, numAirlines, numFlights);
 *    // airportGraph now contains the extracted information from CSV files.
 * @endcode
 */
Graph<string> extractFromDatabase(int &numberOfAirports, int &numberOfAirlines, int &numberOfFlights) {
    string line;
    Graph<string> mainGraph;
    ifstream file2("../csv/airports.csv");
    getline(file2, line); // this is to skip the first line of the file.
    int count = 0;
    while (getline(file2,line, '\n')) {
        stringstream ss(line);
        string airportCode, info;
        getline(ss, airportCode, ',');
        mainGraph.addVertex(airportCode);
        mainGraph.addVertex("P:" + line);
        mainGraph.addEdge(airportCode, "P:" + line, "AIRPORT");
        count++;
    }
    numberOfAirports = count;
    ifstream file3("../csv/flights.csv");
    getline(file3, line, '\n'); // this is to skip the first line of the file.
    count = 0;
    while (getline(file3,line, '\n')) {
        stringstream ss(line);
        string source, target, airline;
        getline(ss, source, ',');
        getline(ss, target, ',');
        getline(ss, airline, ',');
        mainGraph.addEdge(source, target, airline);
        count++;
    }
    numberOfFlights = count;
    ifstream file("../csv/airlines.csv");
    getline(file, line); // this is to skip the first line of the file.
    count = 0;
    while (getline(file, line, '\n')) {
        stringstream ss(line);
        string airlineCode, info;
        getline(ss, airlineCode, ',');
        mainGraph.addVertex("C:" + airlineCode);
        mainGraph.addVertex("L:" + line);
        mainGraph.addEdge("C:" + airlineCode, "L:" + line, "AIRLINE");
        count++;
    }
    numberOfAirlines = count;
    return mainGraph;
}


#endif //PROJETO2AED_EXTRACTFROMDATABASE_H
