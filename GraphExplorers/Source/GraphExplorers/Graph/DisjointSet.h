#pragma once
// ============================================================================
// <copyright file="DisjointSet.h" company="VRK">
//     Copyright (c) Venkata 2020. All rights reserved.
// </copyright>
// ============================================================================


// Local includes, e.g. files in the same folder, typically corresponding declarations.
#include "../DynamicLogger/DynamicLogger.h"

// STL includes.
#include <map>
#include <memory>

// Declarations


// Define gobal constants

namespace vrk {

/**
  @brief: A DisjointSet data structure is not defined in STL. It is fairly standard data structure
          used to represent the partition of a set of elements into disjoint sets in such a way that 
		  common operations such as union (aka merging) of two sets, find opertion which identifies
		  the set the element belongs to.

		  Each element in set have data, parent link, and rank of the element.

		  Below definition I am using "unsigned int" data type of set elements but can be generalize by using
		  template. 
*/

class DisjointSet {
private:

	/**
	 @brief: Internal data structure for set element which consists of data, its parent and rank.
	*/
	struct Element {
		unsigned int m_data;
		unsigned int m_parent;
		unsigned int m_rank;

		Element(unsigned int data, unsigned int parent) : m_data(data),
			                                              m_parent(parent), 
		                                                  m_rank(0){

		}
	};

	/**
	   Maps set element value to internal element data structure set.
	   Note: key value of map should match with Element m_data.
	*/
	mutable std::map<unsigned int, std::shared_ptr<Element>> m_mapElements;

	unsigned int m_setCount;

public:

	/**
	   Adds element to set.

	   @param data value to be added to set.
	   @return true if successfully added, false otherwise.
	*/
	bool AddElement(unsigned int data);

	/**
	   Finds which set data belongs to.

	   @param data for which set to be found.
	   @return set value to which data belongs.
	*/
	unsigned int FindSet(unsigned int data);

	/**
	   Union joins two sets.

	   @param data1 value to be merged.
	   @param data2 value to be merged.
	   @return true if union is success.
	*/
	bool Union(unsigned int data1, unsigned int data2);
	

};
}; // namespace vrk