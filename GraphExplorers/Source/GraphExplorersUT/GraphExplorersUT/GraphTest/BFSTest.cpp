#pragma once
// ============================================================================
// <copyright file="BFSTest.cpp" company="VRK">
//     Copyright (c) Venkata 2021. All rights reserved.
// </copyright>
// ============================================================================

// Local includes, e.g. files in the same folder, typically corresponding declarations.
#include "../../../GraphExplorers/DynamicLogger/DynamicLogger.h"
#include "../../../GraphExplorers/Graph/Graph.h"
#include "../../../GraphExplorers/Graph/BFS.h"

// System includes, e.g. STL, Library headers, ...
#include <list>

// Google test libraries.
#include <gmock/gmock.h> 
#include <gtest/gtestFramework.h>

// Declarations


// define constants

namespace vrk
{
class BFSTestCases : public testing::Test {
protected:
    vrk::BFS* m_pbfsalgo;
public:
    
    BFSTestCases() {
        // initialization code here
        m_pbfsalgo = nullptr;
    }

    void SetUp() {
        // code here will execute just before the test ensues
    }

    void TearDown() {
       // code here will be called just after the test completes
       // ok to through exceptions from here if need be
        delete m_pbfsalgo;
    }
};

TEST_F(BFSTestCases, GoalReachable) {
        TEST_ID("BFS_ALGO_DOF_001_IMPL_NonSIL_DT_ID_001");
        TEST_DESCRIPTION("Test goal reachable from given source");
        TEST_EXPECTED_RESULT("Goal should be reachable");
        
        vrk::DynamicLogger& bfslogger = vrk::DynamicLogger::GetInstance();
        bfslogger.UpdateTraceSettings(false, vrk::LogTraceLevelVal::NoTrace, 0); // disable logs.
        vrk::Graph graph(bfslogger);
        graph.CreateGraph("..\\..\\..\\..\\InputData\\bfsgraph.txt");
        m_pbfsalgo = new BFS(graph, bfslogger);
        std::list<int> path;
        bool isGoalReachable = m_pbfsalgo->IsGoalReachable(1, 3, path);
        ASSERT_EQ(isGoalReachable, true);
        ASSERT_EQ(path.size()-1, 2);
}

TEST_F(BFSTestCases, GoalNotReachable) {
    TEST_ID("BFS_ALGO_DOF_001_IMPL_NonSIL_DT_ID_001");
    TEST_DESCRIPTION("Test goal reachable from given source");
    TEST_EXPECTED_RESULT("Goal should be reachable");

    vrk::DynamicLogger& bfslogger = vrk::DynamicLogger::GetInstance();
    bfslogger.UpdateTraceSettings(false, vrk::LogTraceLevelVal::NoTrace, 0); // disable logs.
    vrk::Graph graph(bfslogger);
    graph.CreateGraph("..\\..\\..\\..\\InputData\\bfsgraph.txt");
    m_pbfsalgo = new BFS(graph, bfslogger);
    std::list<int> path;
    bool isGoalReachable = m_pbfsalgo->IsGoalReachable(1, 7, path);
    ASSERT_EQ(isGoalReachable, false);
}
};