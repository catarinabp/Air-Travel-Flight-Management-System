#include "extractFromDatabase.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Graph.h"
#include "statistics.h"

using testing::Eq;

TEST(Airports, numberOfAirports) {
    auto graph = extractFromDatabase();
    EXPECT_EQ(3019, numberOfAirports(graph));
}



