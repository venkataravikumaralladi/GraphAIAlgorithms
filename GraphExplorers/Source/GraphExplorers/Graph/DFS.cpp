
// ============================================================================
// <copyright file="DFS.cpp" company="VRK">
//     Copyright (c) Venkata 2020. All rights reserved.
// </copyright>
// ============================================================================

#include "Graph.h"
#include "DFS.h"

#include <stack>
#include <set>
#include <memory>

using namespace std;
using namespace vrk;

const std::map<int, vrtxTimes>& DFS::GetVertexPrePostTimes() {

	int numberOfVertices = m_graph.GetNumberOfVertices();
	stack<int> stkVertices;
	const set<int>& vrtxIds = m_graph.GetVerticesIds();
	int currTime  = 1;

	for (auto itr = vrtxIds.begin(); itr != vrtxIds.end(); ++itr) {
		// check if node is not already visited.
		if (m_mapVrtxTimes.find(*itr) == m_mapVrtxTimes.end()) {
			m_mapVrtxTimes.insert(make_pair(*itr, make_pair(currTime, 0)));
			stkVertices.push(*itr);
			currTime++;

			while (!stkVertices.empty()) {
				int iCurrentVertex = stkVertices.top();
				// get adjacent vertices
				auto edges = m_graph.GetVertexDetails(iCurrentVertex)->GetEdges();
				bool isAllChildernProcessed = false;
				for (unsigned int j = 0; j < edges.size(); j++) {

					std::shared_ptr<Vertex> spv = edges[j]->to.lock();
					if (spv != nullptr) {
						if (m_mapVrtxTimes.find(spv->GetId()) != m_mapVrtxTimes.end()) {
							// check if vertex is present then previsit time is added.
							isAllChildernProcessed = true;
							continue;
						}
						else {
							m_mapVrtxTimes.insert(make_pair(spv->GetId(), make_pair(currTime, 0)));
							stkVertices.push(spv->GetId());
							currTime++;
							isAllChildernProcessed = false;
							break;
						} // else part of if condtion of vertex is not visited before.
					} // if condition os spv nullptr
				} // for loop of edges.
				// check if all edges have been processed then pop from stack and add post time.
				if (isAllChildernProcessed) {
					m_mapVrtxTimes[iCurrentVertex].second = currTime;
					currTime++;
					stkVertices.pop();
				} // if condition
			} // while loop
		} // if condition m_mapVrtxTimes.find(*itr) == m_mapVrtxTimes.end()
	} // for loop of vertices
	return m_mapVrtxTimes;
}

int DFS::GetNumberOfSCC() {

	int numberOfVertices = m_graph.GetNumberOfVertices();
	stack<int> stkVertices;
	// is vertex visited.
	map<int, bool> mpVertexVisited; // think this as a chalk mark for nodes visited.

	// get vertices
	const set<int>& vrtxIds = m_graph.GetVerticesIds();
	int numOFSCCs = 0;
	int currTime = 1;
	for (auto itr = vrtxIds.begin(); itr != vrtxIds.end(); ++itr) {
		// check if node is already visited.
		if (mpVertexVisited.find(*itr) == mpVertexVisited.end()) {
			numOFSCCs++;
			mpVertexVisited.insert(make_pair(*itr, true));
			stkVertices.push(*itr);
			currTime++;

			while (!stkVertices.empty()) {
				int iCurrentVertex = stkVertices.top();
				stkVertices.pop(); 
				// get adjacent vertices
				auto edges = m_graph.GetVertexDetails(iCurrentVertex)->GetEdges();
				// loop through all edges.
				for (unsigned int j = 0; j < edges.size(); j++) {
					std::shared_ptr<Vertex> spv = edges[j]->to.lock();
					if (spv != nullptr) {
						// if vertex is already visisted, don't insert in to stack.
						if (mpVertexVisited.find(spv->GetId()) != mpVertexVisited.end()) {
							continue;
						}
						mpVertexVisited.insert(make_pair(spv->GetId(), true));
						stkVertices.push(spv->GetId());
					} // spv if condition
				} // for loop of edges
			} // while loop
		} // if condition m_mapVrtxTimes.find(*itr) == m_mapVrtxTimes.end()
	} // for loop of vertices
	return numOFSCCs;
}