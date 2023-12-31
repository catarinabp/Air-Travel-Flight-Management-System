#include <iostream>
#include <gtest/gtest.h>
#include "menu.h"
#include "statistics.h"
#include "userPreferences.h"
#include "search.h"

UserPreferences preferences;

int main(int argc, char* argv[]) {
    int numberOfAirports = 0;
    int numberOfAirlines = 0;
    int numberOfFlights = 0;
    auto graph = extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights);

    int filter;
    int again = 1;

    while (again == 1) {

        std::cout << std::endl;
        menu::Menu(preferences); //Call menu
        std::cout << "Please choose the option you prefer by writing the number that corresponds to it and then pressing return: " << std::endl;
        std::cin >> filter;

        if (0 > filter && filter > 17) {
            std::cout << std::endl;
            std::cout << "Sorry, that is not a valid option." << std::endl;
            std::cout << std::endl;
            std::cout << "Please choose the option you prefer by writing the number that corresponds to it and then pressing return: " << std::endl;
            std::cin >> filter;
        }

        //Global number of airports
        if (filter == 1) {
            std::cout << "The global number of airports is " << numberOfAirports << std::endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        //Global number of available flights
        if (filter == 2) {
            std::cout << "The global number of available flights is " << numberOfFlights << std::endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        //Number of flights out from an Airport
        if (filter == 3) {
            std::string airportCode;
            std::cout << "Please type the airport's code: ";
            std::cin >> airportCode;
            std::cout << endl;
            std::cout << "The number of flights out from " << airportCode << "Airport is "
                      << numberOfFlightsOut(graph, airportCode) << std::endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        //Number of different airlines with flights departing from an airport
        if (filter == 4) {
            std::string airportCode;
            std::cout << "Please type the airport's code: ";
            std::cin >> airportCode;
            std::cout << endl;
            std::cout << "The number of different airlines with flights departing from " << airportCode << "airport is "
                      << numberOfAirlinesOut(graph, airportCode) << std::endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        //Number of flights per airline
        if (filter == 5) {
            std::string airlineCode;
            std::cout << "Please type the airline's code: ";
            std::cin >> airlineCode;
            std::cout << endl;
            std::cout << "Number of flights of " << airlineCode << "airline is "
                      << numberOfFlightsPerAirline(graph, airlineCode) << std::endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        //Number of flights per city
        if (filter == 6) {
            std::string city;
            std::cout << "Please type the city's name: ";
            std::cin >> city;
            std::cout << endl;
            std::cout << "Number of flights from " << city << " is " << numberOfFlightsPerCity(graph,city) << std::endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }

        }

        //List of destination airports reachable from an airport
        if (filter == 7) {
            std::string airportCode;
            std::cout << "Please type the airport's code: ";
            std::cin >> airportCode;
            std::cout << endl;
            std::cout << "The list of destination airports reachable from " << airportCode
                      << "airport is the following: " << std::endl;
            for(const auto& top: listOfDestinations(graph, airportCode)) {
                std::cout << top << std::endl;
            }
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        //Number of destination airports reachable from an airport
        if (filter == 8) {
            std::string airportCode;
            std::cout << "Please type the airport's code: ";
            std::cin >> airportCode;
            std::cout << endl;
            std::cout << "The number of destinations from " << airportCode
                      << "airport is: " << numberOfDestinationsAirports(listOfDestinations(graph,airportCode)) << std::endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        //Number of cities reachable from an airport
        if (filter == 9) {
            std::string airportCode;
            std::cout << "Please type the airport's code: ";
            std::cin >> airportCode;
            std::cout << endl;
            std::cout << "The number of destiny cities from " << airportCode
                      << "airport is: " << numberOfDestinationsCities(graph, listOfDestinations(graph,airportCode)) << std::endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        //Number of countries reachable from an airport
        if (filter ==10) {
            std::string airportCode;
            std::cout << "Please type the airport's code: ";
            std::cin >> airportCode;
            std::cout << endl;
            std::cout << "The number of destiny countries from " << airportCode
                      << "airport is: " << numberOfDestinationsCountries(graph, listOfDestinations(graph,airportCode)) << std::endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        //Maximum trip and corresponding pair of source-destination airports;
        if (filter ==11) {
            std::string airportCode;
            std::cout << "Please type the airport's code: ";
            std::cin >> airportCode;
            std::cout << endl;
            std::cout << "The maximum trip(s) and corresponding pair(s) of source-destination airports from " << airportCode
                          << "airport are the following: " << endl;
            for(const auto& top: maxTrip(graph,airportCode)) {
                std::cout << top << std::endl;
            }
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        //Top-k airport(s) with the greatest air traffic capacity (with the greatest number of flights)
        if (filter ==12) {
            int k;
            std::cout << "Please type the your chosen k value: ";
            std::cin >> k;
            std::cout << endl;
            std::cout << "The Top-" << k << " airport(s) with the greatest air traffic capacity is the following: " << std::endl;
            for(const auto& top: topAirports(graph,k)) {
                std::cout << top << std::endl;
            }
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        if (filter == 13) {
            std::string airportCode;
            int stops;
            std::cout << "Please type the airport's code: ";
            std::cin >> airportCode;
            std::cout << "Please type the max number of stops: ";
            std::cin >> stops;
            std::cout << endl;
            std::cout << "The number of destination airports reachable from " << airportCode
                      << "airport and with a max of " << stops << "stops is: " << numberOfReachableAirports(graph, airportCode, stops) << std::endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        //Number of cities reachable from an airport
        if (filter == 14) {
            std::string airportCode;
            int stops;
            std::cout << "Please type the airport's code: ";
            std::cin >> airportCode;
            std::cout << "Please type the max number of stops: ";
            std::cin >> stops;
            std::cout << endl;
            std::cout << "The number of destination cities reachable from " << airportCode
                      << "airport and with a max of " << stops << "stops is: " << numberOfReachableCities(graph, airportCode, stops) << std::endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        //Number of countries reachable from an airport
        if (filter ==15) {
            std::string airportCode;
            int stops;
            std::cout << "Please type the airport's code: ";
            std::cin >> airportCode;
            std::cout << "Please type the max number of stops: ";
            std::cin >> stops;
            std::cout << endl;
            std::cout << "The number of destination airports reachable from " << airportCode
                      << "airport and with a max of " << stops << "stops is: " << numberOfReachableCountries(graph, airportCode, stops) << std::endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        if(filter == 16) {
            std::cout << "Please";
            std::string source, destination;
            std::vector<std::string> sources, destinations;
            int sourceOption, destinationOption;
            std::cout << "Let's start by choosing a source: " << std::endl;
            std::cout << "1. Choose by airport Code;" << std::endl;
            std::cout << "2. Choose by airport Name;" << std::endl;
            std::cout << "3. Choose by City;" << std::endl;
            std::cin >> sourceOption;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(sourceOption == 1) {
                std::cout << "Please type the airport code: " << std::endl;
                std::cin >> source;
                sources.push_back(source);
            }
            if(sourceOption == 2) {
                std::cout << "Please type the airport name: " << std::endl;
                std::getline(std::cin, source);
                sources.push_back(nameToCode(graph, source));
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            if(sourceOption == 3) {
                std::cout << "Please type the city's name: " << std::endl;
                std::getline(std::cin, source);
                sources = cityToCode(graph, source);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "Now choose a destiny: " << std::endl;
            std::cout << "1. Choose by airport Code;" << std::endl;
            std::cout << "2. Choose by airport Name;" << std::endl;
            std::cout << "3. Choose by City;" << std::endl;
            std::cin >> destinationOption;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(destinationOption == 1) {
                std::cout << "Please type the airport code: " << std::endl;
                std::cin >> destination;
                destinations.push_back(destination);
            }
            if(destinationOption == 2) {
                std::cout << "Please type the airport name: " << std::endl;
                std::getline(std::cin, destination);
                destinations.push_back(nameToCode(graph, destination));
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            if(destinationOption == 3) {
                std::cout << "Please type the city's name: " << std::endl;
                std::getline(std::cin, destination);
                destinations = cityToCode(graph, destination);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << endl;
            std::cout << "The best flight options from " << source << " to " << destination << " are the following: " << endl;
            vector<vector<string>> all;
            int count = 0;
            for(const auto& single: sources) {
                for(const auto& single2: destinations) {
                    all = findShortestPath(graph, single, single2);
                    if(!all.empty()) {
                        for(const auto& path: all) {
                            for(int i = 0; i < path.size();i++) {
                                if(i % 2 == 0 && i != path.size()-1) {
                                    std::cout << path[i] << " ----";
                                } else if(i % 2 != 0) {
                                    std::cout << path[i] << "----> ";
                                } else {
                                    std::cout << path[i] << std::endl;
                                }
                            }
                        }
                        count++;
                    }
                }
            }
            if(count == 0) {
                cout << "There are no flights from " << source << " to " << destination << "with the selected preferences" << endl;
            }
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while(userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        if(filter == 17) {
            cout << "Always right the code of Airline / Airport." << endl;
            cout << "Always right the name of City / Country." << endl;
            cout << "Leave blank to apply default (null). " << endl;
            cout << endl;
            cout << "Write the code of the preferred Airlines you want to add to the list: " << endl;
            string preferredAirlines;
            cin.ignore(100, '\n');
            getline(cin, preferredAirlines);
            if(!preferredAirlines.empty()) {
                stringstream ss(preferredAirlines);
                string airline;
                while(getline(ss, airline, ',')) {
                    preferences.preferredAirlines.push_back(airline);
                }
            }


            cout << endl;
            cout << "Always right the code of Airline / Airport." << endl;
            cout << "Always right the name of City / Country." << endl;
            cout << "Leave blank to apply default (null). " << endl;
            cout << endl;
            cout << "Write the code of the avoided Airlines you want to add to the list: " << endl;
            string avoidedAirlines;
            cin.ignore(100, '\n');
            getline(cin, avoidedAirlines);
            if(!avoidedAirlines.empty()) {
                stringstream ss2(avoidedAirlines);
                string airline2;
                while(getline(ss2, airline2, ',')) {
                    preferences.avoidedAirlines.push_back(airline2);
                }
            }
            cout << endl;
            cout << "Always right the code of Airline / Airport." << endl;
            cout << "Always right the name of City / Country." << endl;
            cout << "Leave blank to apply default (null). " << endl;
            cout << endl;
            cout << "Write the code of the preferred Airports you want to add to the list: " << endl;
            string preferredAirports;
            cin.ignore(100, '\n');
            getline(cin, preferredAirports);
            if(!preferredAirports.empty()) {
                stringstream ss3(preferredAirports);
                string airport;
                while(getline(ss3, airport, ',')) {
                    preferences.preferredAirports.push_back(airport);
                }
            }
            cout << endl;
            cout << "Always right the code of Airline / Airport." << endl;
            cout << "Always right the name of City / Country." << endl;
            cout << "Leave blank to apply default (null). " << endl;
            cout << endl;
            cout << "Write the code of the avoided Airports you want to add to the list: " << endl;
            string avoidedAirports;
            cin.ignore(100, '\n');
            getline(cin, avoidedAirports);
            if(!avoidedAirports.empty()) {
                stringstream ss4(avoidedAirports);
                string airport2;
                while(getline(ss4, airport2, ',')) {
                    preferences.avoidedAirports.push_back(airport2);
                }
            }
            cout << endl;
            cout << "Always right the code of Airline / Airport." << endl;
            cout << "Always right the name of City / Country." << endl;
            cout << "Leave blank to apply default (null). " << endl;
            cout << endl;
            cout << "Write the code of the preferred Cities you want to add to the list: " << endl;
            string preferredCities;
            cin.ignore(100, '\n');
            getline(cin, preferredAirports);
            if(!preferredCities.empty()) {
                stringstream ss5(preferredAirports);
                string city;
                while(getline(ss5, city, ',')) {
                    preferences.preferredCities.push_back(city);
                }
            }
            cout << endl;
            cout << "Always right the code of Airline / Airport." << endl;
            cout << "Always right the name of City / Country." << endl;
            cout << "Leave blank to apply default (null). " << endl;
            cout << endl;
            cout << "Write the code of the avoided Cities you want to add to the list: " << endl;
            string avoidedCities;
            cin.ignore(100, '\n');
            getline(cin, avoidedCities);
            if(!avoidedCities.empty()) {
                stringstream ss6(avoidedCities);
                string city2;
                while(getline(ss6, city2, ',')) {
                    preferences.avoidedCities.push_back(city2);
                }
            }
            cout << endl;
            cout << "Always right the code of Airline / Airport." << endl;
            cout << "Always right the name of City / Country." << endl;
            cout << "Leave blank to apply default (null). " << endl;
            cout << endl;
            cout << "Write the code of the preferred Countries you want to add to the list: " << endl;
            string preferredCountries;
            cin.ignore(100, '\n');
            getline(cin, preferredCountries);
            if(!preferredCities.empty()) {
                stringstream ss7(preferredCountries);
                string country;
                while(getline(ss7, country, ',')) {
                    preferences.preferredCountries.push_back(country);
                }
            }
            cout << endl;
            cout << "Always right the code of Airline / Airport." << endl;
            cout << "Always right the name of City / Country." << endl;
            cout << "Leave blank to apply default (null). " << endl;
            cout << endl;
            cout << "Write the code of the avoided Countries you want to add to the list: " << endl;
            string avoidedCountries;
            cin.ignore(100, '\n');
            getline(cin, avoidedCountries);
            if(!avoidedCountries.empty()) {
                stringstream ss8(avoidedCountries);
                string country2;
                while(getline(ss8, country2, ',')) {
                    preferences.avoidedCountries.push_back(country2);
                }
            }
            cout << endl;
            cout << "Wait, processing." << endl;
            cout << endl;
            graph = filterGraph(extractFromDatabase(numberOfAirports, numberOfAirlines, numberOfFlights), preferences);
            cout << endl;
            cout << "Preferences updated!" << endl;
            cout << endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while(userInput != 1) {
                std::cout << "Invalid input. Type 1 to return: ";
                std::cin >> userInput;
            }
        }

        //END THE PROGRAM
        if (filter == 0) {
            std::cout << "Thank you!";
            again = 0;
        }
    }
}