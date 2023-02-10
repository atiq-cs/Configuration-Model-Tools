// RandomGraph.cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include "RandomGraph.h"

/* initialize member variables */
RandomGraph::RandomGraph(int nv, int ne) : edge_list(ne) {
	nV = nv;
	nE = ne;
	edge_list.clear();
}

RandomGraph::~RandomGraph() {
}

void RandomGraph::add_edge(int i, int j) {
	CFEdge edge = std::make_pair(i, j);
	edge_list.push_back(edge);
}

CFEdge RandomGraph::get_edge(int i) {
	return edge_list[i];
}

void RandomGraph::sort_edges() {
	// sort using lambda expression 
	std::sort(edge_list.begin(), edge_list.end(), [](CFEdge a, CFEdge b) {
		if (a.first == b.first)
			return a.second < b.second;
		return a.first < b.first;
	});
}
