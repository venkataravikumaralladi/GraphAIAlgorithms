// ============================================================================
// <copyright file="Graph.h" company="VRK">
//     Copyright (c) Venkata 2020. All rights reserved.
// </copyright>
// ============================================================================

#pragma once

// Local includes, e.g. files in the same folder, typically corresponding declarations.
#include "../DynamicLogger/DynamicLogger.h"

// STL includes.
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <set>

// Declarations


// Define gobal constants

namespace vrk {

#define GRAPHINPUTFILENOTOPENED -1

// forward declaration for usage as pointer in Edge class.
class Vertex;

/**
  @brief Requirements tracebility: GRAPH_DOF_001_IMPL_NonSIL <br>
         A edge class defined edge which is part of graph, which points to "to" vertex.
         Pointing vertex "to" is weak pointer which enables pointed vertex life time is
		 independent of "from" vertex.It also consists of value which can be think of
		 weight/cost of that edge. <br>

		 (from vertex) ------cost/weight---------> (to vertex)
*/
class Edge {
public:
	Edge() : weight(0) {}
	std::weak_ptr<Vertex> to;
	int weight;
};

/**
  @brief Requirements tracebility: GRAPH_DOF_001_IMPL_NonSIL <br>
         A Vertex class defines vertex properties. It consists of
         vertex id, and edges it consists of i.e., "to" Vertex 
		 which is part of graph.
*/
class Vertex {

public:

	/**
	   @brief Vertex constructor. Vertex object created with vertex id.
	   @param vertId vertex ID.
	*/
	Vertex(int vertId) : m_id(vertId) {}

	/**
	   @brief GetId returns vertex ID..
	   @param none.
	   @return returns vertex ID.
	*/
	int GetId() { return m_id; }

	/**
	   @brief Inserts edge to this "from" vertex edges vector.
	   @param edge shared pointer to edge.
    */
	void InsertEdge(std::shared_ptr<Edge> edge) {
		m_vecEdges.push_back(edge);
	}

	/**
	   @brief Get edges edges from this vertex. This is similar to MoveGen function 
	   in given in A first course in AI book by Deepak Khemani. Edge vector consists
	   of "to" vertex and weight of that edge.
	   @param none.
	   @return vector of shared pointer edges.
	*/
	std::vector<std::shared_ptr<Edge> > GetEdges() { return m_vecEdges; }

private:
	int m_id;
	std::vector<std::shared_ptr<Edge> > m_vecEdges;
};


/**
  @brief  Requirements tracebility: GRAPH_DOF_001_IMPL_NonSIL <br>
          A Graph reads data from input file and creates graph.
          Graph data is stored in adjacency list.		  
*/
 
class Graph {
public:
	/**
	   @brief Graph constructor creates graph with zero vertices.
	   @param logger instance which is used to log.
	*/
	Graph(DynamicLogger& logger) : m_iNumOfVerticies(0), m_logger(logger) {}

	/**
	   @brief Creates a graph and stored in adjacency list after reading from 
	   input file. Input file should consists of <br>
	   First line consists of number of nodes. <br>
	   following line <source vertex> <to vertex> <weight> <to vertex> <weight> <br>
	   12 <br>
	   1 2 10 3 20 4 30 <br>
	   @param inputFile. Inputfile consists of graph details.
	   @return success or failure.
	*/
	int CreateGraph(std::string inputFile);

	/**
	   @brief Get number of vertices in graph.
	   @param none.
	   @return number of vertices.
	*/
	int GetNumberOfVertices() const { return m_iNumOfVerticies; }

	/**
	   @brief Get all vertex id's present in graph.
	   @param none.
	   @return set of vertices in graph.
	*/
	const std::set<int>& GetVerticesIds() const {
		return m_setVertexIds;
	}

	/**
	   @brief Get vertex details. If vertex id is not present in graph new vertex with given id 
	          is inserted in graph.
	   @param Vertex id for which to get details.
	   @return vertex class shared pointer consists of vertex details.
	*/
	std::shared_ptr<Vertex> GetVertexDetails(int id) const {
		
		auto iter = m_vertices.find(id);
		if (iter != m_vertices.end()) {
			return iter->second;
		}
		else {
			std::shared_ptr<Vertex> vertex = std::make_shared<Vertex>(id);
			m_setVertexIds.insert(id);
			m_vertices.insert(std::make_pair(id, vertex));
			return vertex;
		}
	}

	/**
	   @brief Prints graph in adjaceny list format.
	*/
	void PrintGraph();
	

private:
	// Private internal functions.
	void ParseVertexDetails(const std::string& vertexDetails);
	
	// Private member variables.
	int m_iNumOfVerticies;
	mutable std::map<int, std::shared_ptr<Vertex>> m_vertices;
	mutable std::set<int> m_setVertexIds;
	DynamicLogger& m_logger;
};
} // namespace VRK

