// ============================================================================
// <copyright file="DFS.cpp" company="VRK">
//     Copyright (c) Venkata 2020. All rights reserved.
// </copyright>
// ============================================================================

// Local includes, e.g. files in the same folder, typically corresponding declarations.
#include "Graph.h"
#include "BFS.h"

// System includes, e.g. STL, Library headers, ...
#include <queue>
#include <memory>
#include <list>

using namespace std;
using namespace vrk;


bfsData BFS::ShortestPathFrmSrcUnitLengthEdges(int srcId) {
	m_logger.LogInfo(PRINTDFSDATA, "Number of vertices: ", m_graph.GetNumberOfVertices());
	vector<unsigned int> distFromSrc(m_graph.GetNumberOfVertices()+1, std::numeric_limits<int>::max());
	queue<int> vertexIdsQ;
	vector<unsigned int> parentIds(m_graph.GetNumberOfVertices() + 1, std::numeric_limits<int>::min());

	// initialize srcId distance to zero.
	if (srcId <= m_graph.GetNumberOfVertices()) {
		distFromSrc[srcId] = 0;
		vertexIdsQ.push(srcId);
		parentIds[srcId] = 0;
		// push neighbouring nodes to queue.
		while (!vertexIdsQ.empty()) {
			// pop vertexId from queue.
			unsigned int uiCurrentVertexId = vertexIdsQ.front();
			vertexIdsQ.pop();

			// push neighbours in to queue
			shared_ptr<Vertex> vertexDetails = m_graph.GetVertexDetails(uiCurrentVertexId);
			vector<shared_ptr<Edge>> edges = vertexDetails->GetEdges();
			for (unsigned int j = 0; j < edges.size(); j++) {
				// check if distance is not set.
				shared_ptr<Vertex> spv = edges[j]->to.lock();
				if (spv != nullptr) {
					unsigned int uiToVertexId = spv->GetId();
					if (distFromSrc[uiToVertexId] == std::numeric_limits<int>::max()) {
						// push to queue
						vertexIdsQ.push(uiToVertexId);
						parentIds[uiToVertexId] = uiCurrentVertexId;
						distFromSrc[uiToVertexId] = distFromSrc[uiCurrentVertexId] + 1;
					} // check for max
				}// spv nullptr
			} // for loop of exges
		}
	} // if condition srcId <= m_graph.GetNumberOfVertices()

	return std::make_pair(std::move(distFromSrc), std::move(parentIds));
}

bool BFS::IsGoalReachable(int srcId, int goalId, std::list<int>& path) {
	bfsData data = ShortestPathFrmSrcUnitLengthEdges(srcId);
	
	// If goal node is reachable distance should not be std::numeric_limits<int>::max()
	bool isGoalReachable = false;
	for (unsigned int nodeId = 1; nodeId < data.first.size(); nodeId++) {
		if (nodeId == goalId) {
			if (data.first[nodeId] != std::numeric_limits<int>::max()) {
				isGoalReachable = true;
				break;
			}
		}
	}

	if (isGoalReachable) {
		// get the path
		int currentNode = goalId;
		while (currentNode != srcId) {
			int parent = data.second[currentNode];
			path.push_front(parent);
			currentNode = parent;
		}
		path.push_front(currentNode);
	}
	
	return isGoalReachable;

}