#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    std::cout << "START TESTING" << std::endl << std::endl;
    int res = RUN_ALL_TESTS();

    return res;
}
