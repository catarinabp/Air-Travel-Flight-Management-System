#ifndef PROJETO2AED_STATISTICS_H
#define PROJETO2AED_STATISTICS_H
#include "extractFromDatabase.h"
#include "Graph.h"
#include <string>
#include <unordered_set>

int numberOfAirports(Graph<string> mainGraph) {
    // this function returns the number of airports in the graph.
    int numberOfAirports = 0;
    for (int i = 0; i < mainGraph.getNumVertex(); i++) {
        auto vertex = mainGraph.getVertexSet()[i];
        if(!vertex->getAdj().empty()) {
            if (vertex->getAdj()[0].getAttribute() == "AIRPORT") {
                numberOfAirports++;
            }
        }
    }
    return numberOfAirports;
}

int numFlights(Graph<string> mainGraph) {
    // this function returns the number of flights in the graph.
    int numFlights = mainGraph.getNumEdges();
    return numFlights;
}


#endif //PROJETO2AED_STATISTICS_H
