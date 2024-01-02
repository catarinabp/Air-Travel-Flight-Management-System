#ifndef PROJETO2AED_MENU_H
#define PROJETO2AED_MENU_H
#include "UserPreferences.h"

/**
 * @brief Class representing the menu and user interface.
 */
class menu {
public:
    /**
     * @brief Constructor for the Menu class.
     * @param preferences User preferences for the menu.
     */
    static void Menu(const UserPreferences& preferences);

    /**
     * @brief Displays the user preferences on the menu.
     * @param preferences User preferences to be displayed.
     */
    static void displayPreferences(const UserPreferences& preferences);
    static void Guide();
};

#endif //PROJETO2AED_MENU_H
