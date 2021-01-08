// ============================================================================
// <copyright file="Graph.cpp" company="VRK">
//     Copyright (c) Venkata 2020. All rights reserved.
// </copyright>
// ============================================================================

// Local includes, e.g. files in the same folder, typically corresponding declarations.
#include "Graph.h"


// System includes, e.g. STL, Library headers, ...
#include <iostream>
#include <fstream> // for file
#include <sstream> // for istringstream


// Declarations


// Define global constants

using namespace std;
using namespace vrk;

int Graph::CreateGraph(string inputFileName) {

	ifstream inFile(inputFileName);
	if (!inFile.is_open()) {
		return GRAPHINPUTFILENOTOPENED;
	}

	// redirect input to file.
	std::streambuf* oldcinbuf = std::cin.rdbuf();
	cin.set_rdbuf(inFile.rdbuf());

	cin.clear(); // clear any old buffer in cin stream.
	// read first two comment lines and ignore.
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	// read number of vertices
	cin.clear();
	cin >> m_iNumOfVerticies;
	// ignore the enter
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for (int idx = 0; idx < m_iNumOfVerticies; idx++) {
		std::string presLine;
		std::getline(cin, presLine);
		ParseVertexDetails(presLine);
	}
	
	cin.set_rdbuf(oldcinbuf);
	inFile.close();
	
	return 0;
}

void Graph::ParseVertexDetails(const std::string& vertexDetails) {

	// first one is vertex node.
	istringstream iss(vertexDetails);
	string strVertex;
	bool isSourceVertex = true;
	int iSourceVertex = 0;;
	shared_ptr<Vertex> srcVertex;
	int iOddOrEven = 0;
	int toVertexId = 0;
	while (std::getline(iss, strVertex, ' ')) {
		
		if (isSourceVertex) {
			iSourceVertex = atoi(strVertex.c_str());
			// get source vertex
			srcVertex = GetVertexDetails(iSourceVertex);
			isSourceVertex = false;
			continue;
		}
		if (iOddOrEven % 2 != 0) {
			// store edges
			shared_ptr<Edge> edge = make_shared<Edge>();
			int iWeight = atoi(strVertex.c_str());
			edge->to = GetVertexDetails(toVertexId);
			edge->weight = iWeight;
			srcVertex->InsertEdge(edge);
			iOddOrEven++;
		}
		else {
			// get to vertex
			toVertexId = atoi(strVertex.c_str());
			iOddOrEven++;
		}
	}
}


void Graph::PrintGraph() {

	for (unsigned int i = 1; i <= m_vertices.size(); i++) {
		m_logger.LogInfo(PRINTINPUTGRAPHDATA, "Src vertex: ", m_vertices[i]->GetId(), ". To edges are: ");
		auto edges = m_vertices[i]->GetEdges();
		for (unsigned int j = 0; j < edges.size(); j++) {
			std::shared_ptr<Vertex> spv = edges[j]->to.lock();
			if (spv != nullptr) {
				m_logger.LogInfo(PRINTINPUTGRAPHDATA, spv->GetId(), " weight: ", edges[j]->weight);
			}
		}
	}
	return;
}
