#pragma once
// ============================================================================
// <copyright file="BFSTest.cpp" company="VRK">
//     Copyright (c) Venkata 2021. All rights reserved.
// </copyright>
// ============================================================================

// Local includes, e.g. files in the same folder, typically corresponding declarations.
#include "../../../GraphExplorers/DynamicLogger/DynamicLogger.h"
#include "../../../GraphExplorers/Graph/Graph.h"
#include "../../../GraphExplorers/Graph/DFS.h"

// System includes, e.g. STL, Library headers, ...
#include <list>

// Google test libraries.
#include <gmock/gmock.h> 
#include <gtest/gtestFramework.h>

// Declarations


// define constants

namespace vrk
{
    class DFSTestCases : public testing::Test {
    protected:
        vrk::DFS* m_pdfsalgo;
    public:

        DFSTestCases() {
            // initialization code here
            m_pdfsalgo = nullptr;
        }

        void SetUp() {
            // code here will execute just before the test ensues
        }

        void TearDown() {
            // code here will be called just after the test completes
            // ok to through exceptions from here if need be
            delete m_pdfsalgo;
        }
    };

    TEST_F(DFSTestCases, NumberOfConnectedComponents) {
        TEST_ID("DFS_ALGO_DOF_001_IMPL_NonSIL_DT_ID_001");
        TEST_DESCRIPTION("Test goal reachable from given source");
        TEST_EXPECTED_RESULT("Goal should be reachable");

        vrk::DynamicLogger& dfslogger = vrk::DynamicLogger::GetInstance();
        dfslogger.UpdateTraceSettings(false, vrk::LogTraceLevelVal::NoTrace, 0); // disable logs.
        vrk::Graph graph(dfslogger);
        graph.CreateGraph("..\\..\\..\\..\\InputData\\bfsgraph.txt");
        m_pdfsalgo = new DFS(graph, dfslogger);
        std::list<int> path;
        int num_of_scc = m_pdfsalgo->GetNumberOfSCC();
        ASSERT_EQ(num_of_scc, 1);
    }
};