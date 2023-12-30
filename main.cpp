#include <iostream>
#include <gtest/gtest.h>
#include "menu.h"
#include "statistics.h"


int main(int argc, char* argv[]) {
    //testing::InitGoogleTest(&argc, argv);
    //std::cout << "START TESTING" << std::endl << std::endl;
    //int res = RUN_ALL_TESTS();

    //return res;

    int filter;
    int again = 1;

    while (again == 1) {

        std::cout << std::endl;
        menu::Menu(); //Call menu
        std::cout << "Please choose the option you prefer by writing the number that corresponds to it and then pressing return: " << std::endl;
        std::cin >> filter;

        //while (filter < 0 || filter > 10) {
            //std::cout << std::endl;
            //std::cout << "Sorry, that is not a valid option." << std::endl;
            //std::cout << std::endl;
            //std::cout << "Please choose the option you prefer by writing the number that corresponds to it and then pressing return: " << std::endl;
            //std::cin >> filter;
        //}

        while (!(std::cin >> filter)) {
            std::cout << "Invalid input. Please enter a valid number: ";
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
            std::cout << std::endl;
        }

        //Global number of airports
        if (filter == 1) {
            std::cout << "The global number of airports is " << statistics::numberOfAirports() << std::endl;
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
            std::cout << "The global number of available flights is " << statistics::numFlights() << std::endl;
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
                      << statistics::numberOfFlightsOut(airportCode) << std::endl;
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
                      << statistics::numberOfAirlinesOut(airportCode) << std::endl;
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
                      << statistics::numberOfFlightsPerAirline(airlineCode) << std::endl;
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
            std::cout << "Number of flights from " << city << " is " << statistics::numberOfFlightsPerCity(city) << std::endl;
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
            std::cout << statistics::listOfDestinations(airportCode) << std::endl;
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
            std::cout << "The number of destination airports reachable from " << airportCode
                      << "airport is: " << statistics::numberOfDestinationsAirports(airportCode) << std::endl;
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
            std::cout << "The number of cities reachable from " << airportCode
                      << "airport is: " << statistics::numberOfDestinationsCities(airportCode) << std::endl;
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
            std::cout << "The number of countries reachable from " << airportCode
                      << "airport is: " << statistics::numberOfDestinationsCountries(airportCode) << std::endl;
            std::cout << "\nType 1 to return: ";
            int userInput;
            std::cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
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
