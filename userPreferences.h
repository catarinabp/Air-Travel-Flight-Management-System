#ifndef PROJETO2AED_USERPREFERENCES_H
#define PROJETO2AED_USERPREFERENCES_H

#include <string>
#include <vector>

/**
 * @brief Struct representing user preferences for filtering flights.
 *
 * This struct encapsulates various user preferences for filtering flights based on airlines, countries,
 * airports, and cities.
 *
 * @var preferredAirlines A list of preferred airlines.
 * @var avoidedAirlines A list of airlines to be avoided.
 * @var avoidedCountries A list of countries to be avoided.
 * @var preferredCountries A list of preferred countries.
 * @var avoidedAirports A list of airports to be avoided.
 * @var preferredAirports A list of preferred airports.
 * @var avoidedCities A list of cities to be avoided.
 * @var preferredCities A list of preferred cities.
 *
 * Example Usage:
 * @code
 *    UserPreferences userPrefs;
 *    userPrefs.preferredAirlines = {"Airline1", "Airline2"};
 *    userPrefs.avoidedCountries = {"CountryX", "CountryY"};
 *    // Use userPrefs in your filtering logic...
 * @endcode
 */
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
