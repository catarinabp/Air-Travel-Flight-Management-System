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
    cout << "                 " << 1 << "- Global number of airports" << endl;
    cout << "                 " << 2 << "- Global number of available flights" << endl;
    cout << "                 " << 3 << "- Number of flights out from an airport" << endl;
    cout << "                 " << 4 << "- Number of different airlines with flights departing from an airport" << endl;
    cout << "                 " << 5 << "- Number of flights per airline;" << endl;
    cout << "                 " << 6 << "- Number of flights per city;" << endl;
    cout << "                 " << 7 << "- List of destination airports reachable from an airport;" << endl;
    cout << "                 " << 8 << "- Number of destinations from an airport;" << endl;
    cout << "                 " << 9 << "- Number of destiny cities from an airport;" << endl;
    cout << "                 " << 10 << "- Number of number of destiny countries from an airport;" << endl;
    cout << "                 " << 11 << "- Maximum trip and corresponding pair of source-destination airports;" << endl;
    cout << "                 " << 12 << "- Top-k airport(s) with the greatest air traffic capacity (with the greatest number of flights;" << endl;
    cout << "                 " << 13 << "- Number of destination airports reachable from an airport within X stops;" << endl;
    cout << "                 " << 14 << "- Number of cities reachable from an airport within X stops;" << endl;
    cout << "                 " << 15 << "- Number of countries reachable from an airport within X stops;" << endl;
    cout << endl;
    cout << "-------------------------------------------------- Best Flight Options ------------------------------------------------" << endl;
    cout << endl;
    cout << "                 " << 16 << "- Best Flight Options ------------------------------------------------" << endl;
    cout << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                 " << "Press 0 to quit." << endl;
    cout << endl;
}