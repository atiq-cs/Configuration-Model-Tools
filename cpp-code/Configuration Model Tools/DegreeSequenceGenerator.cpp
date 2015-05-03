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
*
*					Power law degree distribution with constant a and k
*	Status		:	
*/
#include <iostream>
#include <cmath>

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

	std::cout << 0 << " " << nV << std::endl;

	for (int i = 0; i<nV; i++) {
		std::cout << degree << " ";
	}
	// end the file with a new line
	std::cout << std::endl;
}

/*
	Uses the power law equation, y = a * x^k
	We assume the values of a and k constant
	To fix data model we might require to adjust a and k appropriately
*/
void generate_power_law_degree_distribution(int nV, int min_degree, int max_degree) {
	/* Verify degree code block removed
		reason: we correct the last degree of the output when it degree sum is not even
	}*/

	std::cout << 1 << " " << nV << std::endl;

	// assuming values of constants, a and k
	// requires discussion with professor
	double a = 2;
	double k = 2;
	double k_inverse = 1 / k;
	double max_x = pow(double(max_degree) / a, k_inverse);
	double min_x = pow(double(min_degree) / a, k_inverse);
	double interval_x = (max_x - min_x) / (nV-1);
	int degree_sum = 0;

	int i = 0;
	// for (double x = min_x; x < max_x + 2 * std::numeric_limits<double>::epsilon(); x += interval_x; i++) {
	for (double x = min_x; i<nV; x += interval_x, i++) {
		int degree = (int) (a * pow(x, k));
		degree_sum += degree;
		/*if (degree > 190) {
			int y = 10;
			y += 2;
		}*/
		if (i == nV-1 && degree_sum%2) {
			// std::cout << " degree correction happened." << std::endl;
			degree += 1;
		}

		std::cout << degree << " ";
	}
	// end the file with a new line
	std::cout << std::endl;
}
