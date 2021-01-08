#pragma once
// ============================================================================
// <copyright file="BFS.h" company="VRK">
//     Copyright (c) Venkata 2020. All rights reserved.
// </copyright>
// ============================================================================

// Local includes, e.g. files in the same folder, typically corresponding declarations.
#include "Graph.h"
#include "../DynamicLogger/DynamicLogger.h"

// System includes, e.g. STL, Library headers, ...

#include <vector>
#include <memory>
#include <string>
#include <list>

// Declarations


// define constants

namespace vrk {

using bfsData = std::pair<std::vector<unsigned int>, std::vector<unsigned int> >;

/**
 * @brief Requirements tracebility: BFS_ALGO_DOF_001_IMPL_NonSIL <br>
          A Breadth first search (BFS) implements breadth first search algorithm. 	
*/

class BFS {

public:
	/**
	 * @brief BFS constructor 
	 * @param grph Graph on which BFS to be executed.
	 * @param logger dynamic logger to print logs.
	*/
	BFS(const Graph& grph, DynamicLogger& logger) : m_graph(grph), m_logger(logger) { }

	/**
	 * @brief Finds shortest path to every reachable node from source id assuming unit edge length.
	 * @param srcId root node of the graph from which shortest path is found.
	 * @return pair<vector<distance>, vector<parent>>. Here index acts as a vertex id.
	*/
	bfsData ShortestPathFrmSrcUnitLengthEdges(int srcId);
	
	/**
	 * @brief Checks if goal is reachable from given source
	 * @param srcId source id in graph
	 * @param goaldId goal id to be reached in graph
	 * @param path out parameter path from source to goal if goal is reachable. 
	 * @return true if goal is reachable from given source, else false.
	*/
	bool IsGoalReachable(int srcId, int goaldId, std::list<int>& path);

private:
	const Graph& m_graph;
	DynamicLogger& m_logger;

};

}; // namespace vrk

