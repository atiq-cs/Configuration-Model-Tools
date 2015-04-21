// RandomGraph.h
#ifndef RandomGraph_H
#define RandomGraph_H

// edge representation for configuration model graph
typedef std::pair<int, int> CFEdge;

// Class that has all properties and method to store/output the random graph
class RandomGraph {
private:
	int nV;	// number of nodes
	int nE;	// number of edges
	std::vector<CFEdge> edge_list;

public:
	RandomGraph(int nv, int ne);
	~RandomGraph();

	/* void set_num_nodes(int n) { nV = n; }
	void set_num_edges(int n) { nE = n; } */
	int get_num_nodes() { return nV; }
	int get_num_edges() { return nE; }
	void add_edge(int i, int j);
	CFEdge get_edge(int i);
	void sort_edges();
};

#endif
