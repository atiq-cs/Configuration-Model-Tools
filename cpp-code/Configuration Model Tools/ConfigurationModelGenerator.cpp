// ConfigurationModelGenerator.cpp
#include<iostream>
#include <random>
#include "RandomGraph.h"
#include "ConfigurationModelGenerator.h"

/*
Constructor for the class
*/
ConfigurationModelGenerator::ConfigurationModelGenerator() : degree_sum(0) {
}

// Destructor, we exiting program
ConfigurationModelGenerator::~ConfigurationModelGenerator() {
}

// add the degree to the class
void ConfigurationModelGenerator::add_degree(int d) {
	DegreeSequence.push_back(d);
	degree_sum += d;
}

// Validates input degree sequence
// Check if some of degree sequences are even
bool ConfigurationModelGenerator::validate_input() {
	// if not even returns false
	if (degree_sum & 0x1)
		return false;
	return true;
}

// Fixes input degree sequence
void ConfigurationModelGenerator::fix_degree_sequence() {
	if (degree_sum & 0x1) {
		DegreeSequence[DegreeSequence.size() - 1] += 1;
	}
}

// add the degree to the class
void ConfigurationModelGenerator::print_graph(RandomGraph graph) {
	std::cout << graph.get_num_nodes() << " " << graph.get_num_edges() << std::endl;
	for (int i = 0; i < graph.get_num_edges(); i++)
		// std::cout << graph.get_edge(i).first << "," << graph.get_edge(i).second << std::endl;
		std::cout << graph.get_edge(i).first+1 << " " << graph.get_edge(i).second+1 << std::endl;
	// std::cout << std::endl;
}

// Generate the graph, using modern C++ random library
// random ref : http ://stackoverflow.com/questions/19665818/best-way-to-generate-random-numbers-using-c11-random-library
RandomGraph ConfigurationModelGenerator::generate_graph() {
	// create and initialize vectors
	std::vector<int> stub_buffer(degree_sum);
	std::vector<int> stub_list(degree_sum);
	stub_buffer.clear();
	stub_list.clear();

	// initialize random generator
	std::random_device rd;
	std::mt19937 mt(rd());

	// initialize stub list with all the stubs
	// for each of the vertex, insert their indices number of times equal to degree
	int num_vertex = DegreeSequence.size();
	for (int i = 0; i < num_vertex; i++) {
		for (int j = 0; j < DegreeSequence[i]; j++) {
			stub_buffer.push_back(i);
		}
	}

	// generate a random permutation from stub_buffer and store into stub_list
	// for each of the range find a random stub and remove from stub buffer
	while (stub_buffer.empty() == false) {
		int start = 0;
		int end = stub_buffer.size() - 1;
		std::uniform_int_distribution<int> dist(start, end);
		int rand_index = dist(mt);
		stub_list.push_back(stub_buffer[rand_index]);
		stub_buffer.erase(stub_buffer.begin() + rand_index);
	}

	// If we allow duplicate edges, number of edges will be degree_sum instead of degree_sum/2
	RandomGraph randomgraph(num_vertex, degree_sum / 2);
	for (int i = 0; i < degree_sum; i += 2) {
		randomgraph.add_edge(stub_list[i], stub_list[i + 1]);
		// for undirected graph we only keep one edge instead of keeping two where one is duplicate
		// randomgraph.add_edge(stub_list[i+1], stub_list[i]);
	}
	return randomgraph;
}
