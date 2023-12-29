#include <iostream>
#include <gtest/gtest.h>
#include "menu.h"
#include "statistics.h"

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    std::cout << "START TESTING" << std::endl << std::endl;
    int res = RUN_ALL_TESTS();

    return res;

    //Call menu

    int filter;
    int again = 1;

    while (again == 1) {

        std::cout << std::endl;

        menu::Menu();
        std::cout << "Please choose the option you prefer by writing the number that corresponds to it and then pressing return: " << std::endl;
        std::cin >> filter;

        while (filter < 0 || filter > 2) {
            std::cout << std::endl;
            std::cout << "Sorry, that is not a valid option." << std::endl;
            std::cout << std::endl;
        }

        //Global number of airports
        if (filter == 1) {
            std::cout << "The global number of airports is " << numberOfAirports << std::endl;
            std::cout << "\nType 1 to exit: ";
            int exit;
            std::cin >> exit;
        }

        //Global number of available flights
        if (filter == 2) {
            std::cout << "The global number of available flights is " << numFlights << std::endl;
            std::cout << "\nType 1 to exit: ";
            int exit;
            std::cin >> exit;
        }


        //END THE PROGRAM
        if (filter == 0) {
            std::cout << "Thank you!";
            again = 0;
        }
    }
}
