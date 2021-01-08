// ============================================================================
// <copyright file="Disjoint.cpp" company="VRK">
//     Copyright (c) Venkata 2020. All rights reserved.
// </copyright>
// ============================================================================

// Local includes, e.g. files in the same folder, typically corresponding declarations.
#include "DisjointSet.h"


// System includes, e.g. STL, Library headers, ...

// Declarations


// Define global constants

using namespace std;
using namespace vrk;

bool DisjointSet::AddElement(unsigned int data) {
	// check if element is already exists, if not add it.
	if (m_mapElements.find(data) != m_mapElements.end()) {
		return false; // element already present
	}
	m_mapElements.insert(make_pair(data, make_shared<Element>(data, data)));
	return true;
}

unsigned int DisjointSet::FindSet(unsigned int data) {
	// Path compression is used.
	shared_ptr<Element> element;
	if (m_mapElements.find(data) != m_mapElements.end()) {
		element = m_mapElements[data];
		if (data == element->m_parent) {
			return element->m_parent;
		}
		element->m_parent = FindSet(element->m_parent);
	}
	return element->m_parent;
}

bool DisjointSet::Union(unsigned int data1, unsigned int data2) {
	if (m_mapElements.find(data1) != m_mapElements.end() &&
		m_mapElements.find(data2) != m_mapElements.end()) {
		auto element1 = m_mapElements[data1];
		auto element2 = m_mapElements[data2];

		//if parents are same return true, no need to merge.
		if (element1->m_parent == element2->m_parent) {
			return true;
		}
		// now check ranks, how trees to be merged.
		// get parent data
		auto parentOfElement1 = m_mapElements[element1->m_parent];
		auto parentOfElement2 = m_mapElements[element2->m_parent];
		if (parentOfElement1->m_rank > parentOfElement2->m_rank) {
			parentOfElement2->m_parent = parentOfElement1->m_parent;
		}
		else if (parentOfElement1->m_rank < parentOfElement2->m_rank) {
			parentOfElement1->m_parent = parentOfElement2->m_parent;
		}
		else { // both ranks are equal.
			parentOfElement1->m_parent = parentOfElement2->m_parent;
			parentOfElement2->m_rank = parentOfElement2->m_rank + 1;
		}
		return true;
	}
	else {
		return false;
	}

}