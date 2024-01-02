//
// Created by Ana Catarina Patrício on 29/12/2023.
//

#ifndef PROJETO2AED_MENU_H
#define PROJETO2AED_MENU_H
#include "UserPreferences.h"

class menu {
public:
    static void Menu(const UserPreferences& preferences);
    static void displayPreferences(const UserPreferences& preferences);
    static void Guide();
};

#endif //PROJETO2AED_MENU_H
