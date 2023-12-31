#ifndef PROJETO2AED_USERPREFERENCES_H
#define PROJETO2AED_USERPREFERENCES_H

#include <string>
#include <vector>

struct UserPreferences {
    std::vector<std::string> preferredAirlines;
    std::vector<std::string> avoidedAirlines;
    std::vector<std::string> avoidedCountries;
    std::vector<std::string> preferredCountries;
    std::vector<std::string> avoidedAirports;
    std::vector<std::string> preferredAirports;
    std::vector<std::string> avoidedCities;
    std::vector<std::string> preferredCities;
};


#endif //PROJETO2AED_USERPREFERENCES_H
