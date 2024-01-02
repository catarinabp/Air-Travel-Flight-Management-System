#include "menu.h"
#include <iostream>
using namespace std;


void menu::Menu(const UserPreferences& preferences) {
    cout << endl;
    cout << "---------------------------------------------- Statistics of the network ----------------------------------------------" << endl;
    cout << endl;
    cout << "                 " << 1 << "- Global number of airports" << endl;
    cout << "                 " << 2 << "- Global number of available flights" << endl;
    cout << "                 " << 3 << "- Number of flights out from an airport" << endl;
    cout << "                 " << 4 << "- Number of different airlines with flights departing from an airport" << endl;
    cout << "                 " << 5 << "- Number of flights per airline;" << endl;
    cout << "                 " << 6 << "- Number of flights per city;" << endl;
    cout << "                 " << 7 << "- List of destination airports reachable from an airport;" << endl;
    cout << "                 " << 8 << "- Number of destinations from an airport;" << endl;
    cout << "                 " << 9 << "- Number of destiny cities from an airport;" << endl;
    cout << "                 " << 10 << "- Number destiny countries from an airport;" << endl;
    cout << "                 " << 11 << "- Maximum trip and corresponding pair of source-destination airports;" << endl;
    cout << "                 " << 12 << "- Top-k airport(s) with the greatest air traffic capacity (with the greatest number of flights;" << endl;
    cout << "                 " << 13 << "- Number of destination airports reachable from an airport within X stops;" << endl;
    cout << "                 " << 14 << "- Number of cities reachable from an airport within X stops;" << endl;
    cout << "                 " << 15 << "- Number of countries reachable from an airport within X stops;" << endl;
    cout << endl;
    cout << "-------------------------------------------------- Best Flight Options ------------------------------------------------" << endl;
    cout << endl;
    cout << "                 " << 16 << "- Best Flight Options;" << endl;
    cout << endl;
    cout << "------------------------------------------------------- PREFERENCES ---------------------------------------------------" << endl;
    cout << endl;
    cout << "                 " << 17 << "- Edit system preferences;" << endl;
    cout << endl;
    displayPreferences(preferences);
    cout << "--------------------------------------------------------- GUIDE -------------------------------------------------------" << endl;
    cout << endl;
    cout << "                 " << 18 << "- Review how to write the arguments for the search filters;" << endl;
    cout << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "                 " << "Press 0 to quit." << endl;
    cout << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
}

void menu::displayPreferences(const UserPreferences& preferences) {

    if(!preferences.preferredAirlines.empty()) {
        std::cout << "                 " << "Preferred Airlines: ";
        for(const auto& top: preferences.preferredAirlines) {
            if (top == preferences.preferredAirlines.back()) {
                std::cout << top;
            } else {
                std::cout << top << ", ";
            }
        }
        std::cout << std::endl;
    }
    if(!preferences.avoidedAirlines.empty()) {
        std::cout << "                 " << "Avoided Airlines: ";
        for(const auto& top: preferences.avoidedAirlines) {
            if (top == preferences.avoidedAirlines.back()) {
                std::cout << top;
            } else {
                std::cout << top << ", ";
            }
        }
        std::cout << std::endl;
    }
    if(!preferences.preferredAirports.empty()) {
        std::cout << "                 " << "Preferred Airports: ";
        for(const auto& top: preferences.preferredAirports) {
            if (top == preferences.preferredAirports.back()) {
                std::cout << top;
            } else {
                std::cout << top << ", ";
            }
        }
        std::cout << std::endl;
    }
    if(!preferences.avoidedAirports.empty()) {
        std::cout << "                 " << "Avoided Airports: ";
        for(const auto& top: preferences.avoidedAirports) {
            if (top == preferences.avoidedAirports.back()) {
                std::cout << top;
            } else {
                std::cout << top << ", ";
            }
        }
        std::cout << std::endl;
    }
    if(!preferences.preferredCities.empty()) {
        std::cout << "                 " << "Preferred Cities: ";
        for(const auto& top: preferences.preferredCities) {
            if (top == preferences.preferredCities.back()) {
                std::cout << top;
            } else {
                std::cout << top << ", ";
            }
        }
        std::cout << std::endl;
    }
    if(!preferences.avoidedCities.empty()) {
        std::cout << "                 " << "Avoided Cities: ";
        for(const auto& top: preferences.avoidedCities) {
            if (top == preferences.avoidedCities.back()) {
                std::cout << top;
            } else {
                std::cout << top << ", ";
            }
        }
        std::cout << std::endl;
    }
    if(!preferences.preferredCountries.empty()) {
        std::cout << "                 " << "Preferred Countries: ";
        for(const auto& top: preferences.preferredCountries) {
            if (top == preferences.preferredCountries.back()) {
                std::cout << top;
            } else {
                std::cout << top << ", ";
            }
        }
        std::cout << std::endl;
    }
    if(!preferences.avoidedCountries.empty()) {
        std::cout << "                 " << "Avoided Countries: ";
        for(const auto& top: preferences.avoidedCountries) {
            if (top == preferences.avoidedCountries.back()) {
                std::cout << top;
            } else {
                std::cout << top << ", ";
            }
        }
        std::cout << std::endl;
    }
}

void menu::Guide() {
    cout << "How should I write the arguments of the search filters?" << endl;
    cout << endl;
    cout << "   Airport's code (acronym)" << endl;
    cout << "     - All uppercase letters (e.g. OPO)" << endl;
    cout << endl;
    cout << "   Airline's code (acronym)" << endl;
    cout << "     - All uppercase letters (e.g. TAP)" << endl;
    cout << endl;
    cout << "   City's /Country's name ***" << endl;
    cout << "     - The first letter uppercase and the following lowercase " << endl;
    cout << "       (e.g. Oporto, Portugal)" << endl;
}