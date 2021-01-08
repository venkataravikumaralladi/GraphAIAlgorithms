// ============================================================================
// <copyright file="Main.cpp" company="VRK">
//     Copyright (c) Venkata 2020. All rights reserved.
// </copyright>
// ============================================================================

// local headers
#include "DynamicLogger/DynamicLogger.h"
#include "Graph/Graph.h"
#include "Graph/DFS.h"
#include "Graph/BFS.h"

// standard headers
#include <iostream>
#include <cmath>

using namespace std;
using namespace vrk;

int main() {
	cout << "Main called." << endl;

	vrk::DynamicLogger& logger = vrk::DynamicLogger::GetInstance();
	logger.UpdateTraceSettings(true, vrk::LogTraceLevelVal::TraceAll, PRINTMANDATORY);
	
	// DFS test.
	{
		Graph graph(logger);
		graph.CreateGraph("..\\..\\..\\InputData\\graph.txt");
		//graph.PrintGraph();

		// DFS analysis on graph
		vrk::DFS dfs(graph, logger);
		cout << "\nNumber of SCCs are " << dfs.GetNumberOfSCC() << endl;

		// DFS get pre and post times
		const std::map<int, vrtxTimes>& times = dfs.GetVertexPrePostTimes();

		for (auto itr = times.begin(); itr != times.end(); itr++) {
			cout << "Vertex " << itr->first << " pretime: " << itr->second.first << " posttime: " << itr->second.second << endl;
		}
	}

	// BFS test
	{
		cout << "********************** BFS test ************************* " << endl;
		Graph graph(logger);
		graph.CreateGraph("..\\..\\..\\InputData\\bfsgraph.txt");
		vrk::BFS bfs(graph, logger);
		bfsData data = bfs.ShortestPathFrmSrcUnitLengthEdges(1);
		cout << "Shortest path from source 1: " << endl;
		for (unsigned int i = 1; i < data.first.size(); i++) {
			cout << "Vertex: " << i << " is " << data.first[i] << endl;
		}

		cout << "BFS tree for source 1: " << endl;
		for (unsigned int i = 1; i < data.second.size(); i++) {
			cout << "Parent: " << i << " is " << data.second[i] << endl;
		}
	}

	{
		cout << "Iterative algorithm-----------------------" << endl;
		double n = 1000;
		int count = 0;
		while (n >= 1) {
			n = std::log2(n);
			cout << n << endl;
			count++;
		}
		cout << "count is " << count << endl;
	}



}
