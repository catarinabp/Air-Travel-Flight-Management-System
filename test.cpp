#include "extractFromDatabase.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Graph.h"
#include "statistics.h"

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
// test the function numberOfReachableCities from statistics.h, give only 3 examples
TEST(Statistics, numberOfReachableCities) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);

    EXPECT_EQ(743, numberOfReachableCities(graph, "OPO", 2));
    EXPECT_EQ(2761, numberOfReachableCities(graph, "LAX", 3));
    EXPECT_EQ(2880, numberOfReachableCities(graph, "YEG", 4));
    EXPECT_EQ(2977, numberOfReachableCities(graph, "CDG", 5));
}
