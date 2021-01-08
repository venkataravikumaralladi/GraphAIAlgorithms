// ============================================================================
// <copyright file="GraphTest.cpp" company="VRK">
//     Copyright (c) Venkata 2021. All rights reserved.
// </copyright>
// ============================================================================

// Local includes, e.g. files in the same folder, typically corresponding declarations.
#include "../../../GraphExplorers/DynamicLogger/DynamicLogger.h"
#include "../../../GraphExplorers/Graph/Graph.h"

// System includes, e.g. STL, Library headers, ...

// Google test libraries.
#include <gmock/gmock.h> 
#include <gtest/gtestFramework.h>

// Declarations


// define constants


/*
* simple test declaration requires use of the TEST macro below. The TEST
macro takes two parameters: the name of the test case and a descriptive
name for the test. A test case, per Google’s documentation, is a related
collection of tests that can “share data and subroutines.”2 (The term is
overloaded; to some, a test case represents a single scenario.)
Reading the test case name and test name together, left to right, reveals
a sentence that describes what we want to verify: “Soundex encoding
retains [the] sole letter of [a] one-letter word.”
*/



namespace vrk
{
class GraphParsing : public testing::Test {
public:
    vrk::DynamicLogger& logger = vrk::DynamicLogger::GetInstance();
};
    
TEST_F(GraphParsing, DISABLED_ReadGraphDataFromFileToConatiners) {
    TEST_ID("GRAPH_DOF_001_IMPL_NonSIL_DT_ID_001");
    TEST_DESCRIPTION("Test reading graph data from input file to containers");
    TEST_EXPECTED_RESULT("Number of vertices read correctly. Returns 12");
    vrk::Graph graph(logger);
    graph.CreateGraph("..\\..\\..\\..\\InputData\\graph.txt");
    logger.UpdateTraceSettings(false, vrk::LogTraceLevelVal::NoTrace, 0); // disable logs.
    int numberOfVertices = graph.GetNumberOfVertices();
    ASSERT_THAT(graph.GetNumberOfVertices(), 12);
    
}

TEST_F(GraphParsing, ReadGraphDataFromFileDoesnotExist) {
    TEST_ID("GRAPH_DOF_001_IMPL_NonSIL_DT_ID_002");
    TEST_DESCRIPTION("Test graph input file doesnot exist");
    TEST_EXPECTED_RESULT("File not opened. Returns GRAPHINPUTFILENOTOPENED");
    vrk::Graph graph(logger);
    int retVal = graph.CreateGraph("..\\..\\..\\..\\InputData\\graph1.txt");
    logger.UpdateTraceSettings(false, vrk::LogTraceLevelVal::NoTrace, 0); // disable logs.
    ASSERT_THAT(retVal, GRAPHINPUTFILENOTOPENED);
}

TEST_F(GraphParsing, CheckFloatingValuesEquality) {
    double x{ 4.0 };
    double y{ 0.56 };
    ASSERT_THAT(x + y, testing::DoubleEq(4.56));
}

};