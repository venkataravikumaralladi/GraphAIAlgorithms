// ============================================================================
// <copyright file="DFS.h" company="VRK">
//     Copyright (c) Venkata 2020. All rights reserved.
// </copyright>
// ============================================================================
#pragma once

// Local includes, e.g. files in the same folder, typically corresponding declarations.
#include "Graph.h"
#include "../DynamicLogger/DynamicLogger.h"

// System includes, e.g. STL, Library headers, ...

#include <map>
#include <memory>
#include <string>

// Declarations


// Define global constants

namespace vrk {

// stores prevertex time and post vertex time.
using vrtxTimes = std::pair<int, int>;

/**
  @brief  Requirements tracebility: DFS_ALGO_DOF_001_IMPL_NonSIL <br>
          A Depth first search related algorithms.
          This class provides.
		  1. Number of strongly connected components (SCC).
		  2. Pre and post times of vertices in graph.
		  3. Check if cycles are present in graph.
*/
class DFS {
public:

	/**
	   @brief DFS constructor.
	   @param graph: input graph on which algorithms to be run.
	   @param logger: logger which is used to log information.
	*/
	DFS(const Graph& grph, DynamicLogger & logger) : m_graph(grph), m_logger(logger) { }

	/**
	   @brief Gets number of strongly connected components in input graph.
	   @param graph: input graph on which algorithms to be run.
	   @return number of strongly connected components in graph.
	*/
	int GetNumberOfSCC();

	/**
	   @brief Gets pre and post vertex times of vertexes in graph.
	   @param none.
	   @return map of vertices and their corresponding pre and post times.
	*/
	const std::map<int, vrtxTimes>& GetVertexPrePostTimes();

private:
	const Graph& m_graph;
	DynamicLogger& m_logger;
	std::map<int, vrtxTimes> m_mapVrtxTimes;
};
} // namespace vrk
