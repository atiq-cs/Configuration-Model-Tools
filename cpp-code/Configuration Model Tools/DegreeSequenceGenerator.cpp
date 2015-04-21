// DegreeSequenceGenerator.cpp

/*
*	Problem Title:	Degree Sequence Generator
*	Date		:	April 20, 2015
*	Author		:	Atiqur Rahman (mdarahman@cs.stonybrook.edu)
*	Desc		:	
*					Supports two types
*					Uniform degree sequence generator: input format
*					  Number of vertices follows with,
*						number of degree sequences we want for provided number of vertices
*					Power law formula: x = [(x1^(n+1) - x0^(n+1))*y + x0^(n+1)]^(1/(n+1))
*	Status		:	
*/
#include <iostream>


// generate_power_law_degree_distribution

void generate_uniform_degree_distribution(int nV, int degree) {
	// verify degree
	if (degree % 2 == 1) {
		std::cerr << "Sum of degree sequences is not even! This input graph configuration will be skipped." << \
			std::endl;
		return;
	}
	else if (nV == 1 && degree>0) {
		std::cerr << "Specified number of degree is invalid for a single vertex graph." << std::endl;
		return;
	}

	std::cout << nV << std::endl;

	for (int i = 0; i<nV; i++) {
		std::cout << degree << " ";
	}
	// end the file with a new line
	std::cout << std::endl;
}
