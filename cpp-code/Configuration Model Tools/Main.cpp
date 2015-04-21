/*
*	Problem Title:	Configuration Model Tools
*	Date		:	April 20, 2015
*	Author		:	Atiqur Rahman (mdarahman@cs.stonybrook.edu)
*	Desc		:	Main program
*					take a set of input degree sequence and generate a random graph
*					with same set of degree sequence for each of the vertex
*					  Terminates for input 0 nunber of vertices
*					Output:
*
*	Status		:	
*/

#include <random>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include "DegreeSequenceGenerator.h"
#include "ConfigurationModelGenerator.h"
#include "RandomGraph.h"

#define FILE_IO	TRUE

// My own file template for C++
#ifdef FILE_IO
#include <fstream>
#endif


int main() {
	{
#ifdef FILE_IO
		// reason why file open might fail in MAC OS X, had to change working directory ref:
// http://stackoverflow.com/questions/14476655/code-runs-perfect-in-g-but-not-in-xcode-cannot-find-file/14478210#14478210
		
		std::ifstream inFile("ds-input.txt");	// input for this program
		if (inFile.good() == false) {
			std::cout << "File open for reading failed!! Exiting." << std::endl;
			return 0;
		}
		std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
		std::cin.rdbuf(inFile.rdbuf()); //redirect std::cin to inFile!

		std::ofstream outFile("ds-output.txt");	// output for this program
		if (inFile.good() == false) {
			std::cout << "File open for writing failed!! Exiting." << std::endl;
			return 0;
		}
		std::streambuf *coutbuf = std::cout.rdbuf();
		std::cout.rdbuf(outFile.rdbuf());
#endif

		bool is_power_law;
		int num_vertices, degree;

		// Take each input line
		while (std::cin >> is_power_law >> num_vertices >> degree) {

			// Code for power law degree distribution
			if (is_power_law == true) {
				// generate_power_law_degree_distribution(num_vertices, degree);
			}
			// Code for uniform degree distribution
			else {
				generate_uniform_degree_distribution(num_vertices, degree);
			}
		}

#ifdef FILE_IO
		std::cin.rdbuf(cinbuf);
		inFile.close();
		std::cout.rdbuf(coutbuf);
		outFile.close();
#endif
		// file copy
		std::ifstream  src("ds-output.txt", std::ios::binary);
		std::ofstream  dst("cf-input.txt", std::ios::binary);
		dst << src.rdbuf();
	}


	// ref: http://en.cppreference.com/w/cpp/chrono/duration
	std::chrono::seconds file_IO_interval(2);
	// ref: http://en.cppreference.com/w/cpp/thread/sleep_for
	std::this_thread::sleep_for(file_IO_interval);

	// Second part: Random Graph Generator
	{
#ifdef FILE_IO
		std::ifstream inFile("cf-input.txt");
		std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
		std::cin.rdbuf(inFile.rdbuf()); //redirect std::cin to inFile!

		std::ofstream outFile("cf-output.txt");
		std::streambuf *coutbuf = std::cout.rdbuf();
		std::cout.rdbuf(outFile.rdbuf());
#endif

		int num_vertices = 0;
		while (std::cin >> num_vertices && num_vertices) {
			ConfigurationModelGenerator modelgenerator;

			int degree = 0;
			// add input degree sequence to ConfigurationModelGenerator
			for (int i = 0; i < num_vertices; i++) {
				std::cin >> degree;
				modelgenerator.add_degree(degree);
			}

			if (modelgenerator.validate_input() == false) {
				std::cerr << "Sum of degree sequences is not even! This degree sequence will be skipped." << \
					std::endl;
				return 0;
			}

			RandomGraph randomgraph = modelgenerator.generate_graph();
			randomgraph.sort_edges();
			modelgenerator.print_graph(randomgraph);
		}

#ifdef FILE_IO
		std::cin.rdbuf(cinbuf);
		inFile.close();
		std::cout.rdbuf(coutbuf);
		outFile.close();
#endif

	}
	return 0;
}