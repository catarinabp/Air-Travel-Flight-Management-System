#include "extractFromDatabase.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Graph.h"
#include "statistics.h"
#include "search.h"

using testing::Eq;

TEST(Airports, numberOfAirports) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);
    EXPECT_EQ(3019, numberOfAirports);
}

//test the number of flights
TEST(Flights, numberOfFlights) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);
    EXPECT_EQ(63832, numberOfFlights);
}
//test the number of airlines
TEST(Airlines, numberOfAirlines) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);
    EXPECT_EQ(444, numberOfAirlines);
}
// test the function numberOfFlightsOut from statistics.h, give only 3 examples
TEST(Statistics, numberOfFlightsOut) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);
    EXPECT_EQ(100, numberOfFlightsOut(graph, "OPO"));
    EXPECT_EQ(491, numberOfFlightsOut(graph, "LAX"));
    EXPECT_EQ(64, numberOfFlightsOut(graph, "YEG"));
    EXPECT_EQ(518, numberOfFlightsOut(graph, "CDG"));
}
// test the function numberOfAirlinesOut from statistics.h, give only 3 examples
TEST(Statistics, numberOfAirlinesOut) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);
    EXPECT_EQ(22, numberOfAirlinesOut(graph, "OPO"));
    EXPECT_EQ(61, numberOfAirlinesOut(graph, "LAX"));
}
// test the function numberOfFlightsPerAirline from statistics.h, give only 3 examples
TEST(Statistics, numberOfFlightsPerAirline) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);
    EXPECT_EQ(222, numberOfFlightsPerAirline(graph, "FFT"));
    EXPECT_EQ(1960, numberOfFlightsPerAirline(graph, "USA"));
    EXPECT_EQ(549, numberOfFlightsPerAirline(graph, "BAW"));
}
// test the function numberOfFlightsPerCity from statistics.h, give only 3 examples
TEST(Statistics, numberOfFlightsPerCity) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);
    EXPECT_EQ(719, numberOfFlightsPerCity(graph, "Paris"));
    EXPECT_EQ(491, numberOfFlightsPerCity(graph, "Los Angeles"));
    EXPECT_EQ(64, numberOfFlightsPerCity(graph, "Edmonton"));
}

// test the function numberOfDestinationsAirports from statistics.h, give only 3 examples
TEST(Statistics, numberOfDestinationsAirports) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);
    vector<string> airports = listOfDestinations(graph, "OPO");
    EXPECT_EQ(61, numberOfDestinationsAirports(airports));
    airports = listOfDestinations(graph, "LAX");
    EXPECT_EQ(149, numberOfDestinationsAirports(airports));
    airports = listOfDestinations(graph, "YEG");
    EXPECT_EQ(35, numberOfDestinationsAirports(airports));
    airports = listOfDestinations(graph, "CDG");
    EXPECT_EQ(236, numberOfDestinationsAirports(airports));
}
// test the function numberOfDestinationsCities from statistics.h, give only 3 examples
TEST(Statistics, numberOfDestinationsCities) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);

    vector<string> airports = listOfDestinations(graph, "OPO");
    EXPECT_EQ(57, numberOfDestinationsCities(graph, airports));
    airports = listOfDestinations(graph, "LAX");
    EXPECT_EQ(142, numberOfDestinationsCities(graph, airports));
    airports = listOfDestinations(graph, "YEG");
    EXPECT_EQ(35, numberOfDestinationsCities(graph, airports));
    airports = listOfDestinations(graph, "CDG");
    EXPECT_EQ(231, numberOfDestinationsCities(graph, airports));
}
// test the function numberOfDestinationsCountries from statistics.h, give only 3 examples
TEST(Statistics, numberOfDestinationsCountries) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);

    vector<string> airports = listOfDestinations(graph, "OPO");
    EXPECT_EQ(16, numberOfDestinationsCountries(graph, airports));
    airports = listOfDestinations(graph, "LAX");
    EXPECT_EQ(35, numberOfDestinationsCountries(graph, airports));
    airports = listOfDestinations(graph, "YEG");
    EXPECT_EQ(5, numberOfDestinationsCountries(graph, airports));
    airports = listOfDestinations(graph, "CDG");
    EXPECT_EQ(104, numberOfDestinationsCountries(graph, airports));
}
// test the function numberOfReachableDestinations from statistics.h, give only 3 examples
TEST(Statistics, numberOfReachableAirports) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);

    EXPECT_EQ(743, numberOfReachableAirports(graph, "OPO", 2));
    EXPECT_EQ(2761, numberOfReachableAirports(graph, "LAX", 3));
    EXPECT_EQ(2880, numberOfReachableAirports(graph, "YEG", 4));
    EXPECT_EQ(2977, numberOfReachableAirports(graph, "CDG", 5));
}
// test the function numberOfReachableDestinations from statistics.h, give other 3 examples
TEST(Statistics, numberOfReachableAirports2) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);

    EXPECT_EQ(1125, numberOfReachableAirports(graph, "LIS", 9));
    EXPECT_EQ(369, numberOfReachableAirports(graph, "LAE", 3));
    EXPECT_EQ(2807, numberOfReachableAirports(graph, "LOS", 4));
}

// test the function numberOfCities from statistics.h, give only 3 examples
TEST(Statistics, numberOfReacheableCities) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;

    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);

    EXPECT_EQ(707, numberOfReacheableCities(graph, "OPO", 2));
    EXPECT_EQ(2664, numberOfReacheableCities(graph, "LAX", 3));
    EXPECT_EQ(2781, numberOfReacheableCities(graph, "YEG", 4));
    EXPECT_EQ(2874, numberOfReacheableCities(graph, "CDG", 5));
}
// test the function numberOfReacheableCountries from statistics.h, give only 3 examples
TEST(Statistics, numberOfReacheableCountries) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;

    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);

    EXPECT_EQ(164, numberOfReacheableCountries(graph, "OPO", 2));
    EXPECT_EQ(223, numberOfReacheableCountries(graph, "LAX", 3));
    EXPECT_EQ(223, numberOfReacheableCountries(graph, "YEG", 4));
    EXPECT_EQ(225, numberOfReacheableCountries(graph, "CDG", 5));
}
// test the function maxTrip from statistics.h, give only 3 examples
TEST(Statistics, maxTrip) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;

    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);

    EXPECT_EQ(1, maxTrip(graph, "OPO").size());
    EXPECT_EQ(1, maxTrip(graph, "LAX").size());
    EXPECT_EQ(3, maxTrip(graph, "YEG").size());
    EXPECT_EQ(2, maxTrip(graph, "CDG").size());
}

//test the function topAirports from statistics.h.
TEST(Statistics, topAirports) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;

    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);

    auto airports = topAirports(graph, 10);
    EXPECT_EQ("ATL", airports[0]);
    EXPECT_EQ("ORD", airports[1]);
    EXPECT_EQ("PEK", airports[2]);
    EXPECT_EQ("LHR", airports[3]);
    EXPECT_EQ("CDG", airports[4]);
    EXPECT_EQ("FRA", airports[5]);
    EXPECT_EQ("LAX", airports[6]);
    EXPECT_EQ("DFW", airports[7]);
    EXPECT_EQ("JFK", airports[8]);
    EXPECT_EQ("AMS", airports[9]);
}

// test the function findShortestPath from search.h
TEST(Search, findShortestPath) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;

    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);
    string sourceAirport = "OPO";
    string destinationAirport = "LAX";
    auto shortestPath = findShortestPath(graph, sourceAirport, destinationAirport);

}