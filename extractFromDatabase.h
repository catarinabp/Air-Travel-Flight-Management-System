#ifndef PROJETO2AED_EXTRACTFROMDATABASE_H
#define PROJETO2AED_EXTRACTFROMDATABASE_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"

using namespace std;

Graph<string> extractFromDatabase() {
    ifstream file("../airlines.csv");
    string line;
    Graph<string> mainGraph;
    /* getline(file, line); // this is to skip the first line of the file.
    while (getline(file, line)) {
        stringstream ss(line);
        string airlineCode, airlineName, airlineCallsign, airlineCountry;
        getline(ss, airlineCode, ',');
        getline(ss, airlineName, ',');
        getline(ss, airlineCallsign, ',');
        getline(ss, airlineCountry, ',');
        if (mainGraph.findVertex(airlineCode) == NULL) {
            mainGraph.addVertex(airlineCode);
            mainGraph.addVertex(airlineName);
            mainGraph.addVertex(airlineCallsign);
            mainGraph.addVertex(airlineCountry);
            mainGraph.addEdge(airlineCode, airlineName, 2, "AIRLINE");
            mainGraph.addEdge(airlineCode, airlineCallsign, 2, "AIRLINE");
            mainGraph.addEdge(airlineCode, airlineCountry, 2, "AIRLINE");
        }
    } */
    ifstream file2("../airports.csv");
    getline(file2, line); // this is to skip the first line of the file.
    while (getline(file2,line, '\n')) {
        stringstream ss(line);
        string airportCode, airportName, airportCity, airportCountry, airportLatitude, airportLongitude;
        getline(ss, airportCode, ',');
        getline(ss, airportName, ',');
        getline(ss, airportCity, ',');
        getline(ss, airportCountry, ',');
        getline(ss, airportLatitude, ',');
        getline(ss, airportLongitude, ',');
        if (mainGraph.findVertex(airportCode) == NULL) {
            mainGraph.addVertex(airportCode);
            mainGraph.addVertex(airportName);
            mainGraph.addVertex(airportCity);
            mainGraph.addVertex(airportCountry);
            mainGraph.addVertex(airportLatitude);
            mainGraph.addVertex(airportLongitude);
            mainGraph.addEdge(airportCode, airportName, 3, "AIRPORT");
            mainGraph.addEdge(airportCode, airportCity, 3, "AIRPORT");
            mainGraph.addEdge(airportCode, airportCountry, 3, "AIRPORT");
            mainGraph.addEdge(airportCode, airportLatitude, 3, "AIRPORT");
            mainGraph.addEdge(airportCode, airportLongitude, 3, "AIRPORT");
        }
    }
    ifstream file3("../flights.csv");
    getline(file3, line, '\n'); // this is to skip the first line of the file.
    while (getline(file3,line, '\n')) {
        stringstream ss(line);
        string source, target, airline;
        getline(ss, source, ',');
        getline(ss, target, ',');
        getline(ss, airline, ',');
        mainGraph.addEdge(source, target, 1, airline);
    }

    return mainGraph;
}

#endif //PROJETO2AED_EXTRACTFROMDATABASE_H
