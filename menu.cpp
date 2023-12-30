//
// Created by Ana Catarina Patrício on 29/12/2023.
//

#include "menu.h"
#include <iostream>
using namespace std;


void menu::Menu() {
    cout << endl;
    cout << "---------------------------------------------- Statistics of the network ----------------------------------------------" << endl;
    cout << endl;
    cout << "                 " << 1 << "Global number of airports" << endl;
    cout << "                 " << 2 << "Global number of available flights" << endl;
    cout << "                 " << 3 << "Number of flights out from an airport" << endl;
    cout << "                 " << 4 << "Number of different airlines with flights departing from an airport" << endl;
    cout << "                 " << 5 << "Number of flights per airline;" << endl;
    cout << "                 " << 6 << "Number of flights per city;" << endl;
    cout << "                 " << 7 << "List of destination airports reachable from an airport;" << endl;
    cout << "                 " << 8 << "Number of destination airports reachable from an airport;" << endl;
    cout << "                 " << 9 << "Number of cities reachable from an airport;" << endl;
    cout << "                " << 10 << "Number of countries reachable from an airport;" << endl;
    cout << endl;
    cout << "                 " << "Press 0 to quit." << endl;
    cout << endl;
}