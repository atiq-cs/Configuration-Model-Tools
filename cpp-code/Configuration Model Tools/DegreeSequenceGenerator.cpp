/*  DegreeSequenceGenerator.cpp
*	Problem Title:	Degree Sequence Generator
*	Updated		:	May 14, 2015
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

void generate_uniform_degree_distribution(int nV, int degree) {
	// verify degree
	if ((nV * degree) % 2 == 1) {
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
Power law degree distribution implementation
Normalization is performed from min degree to max degree
negative power

k is the power of power law, actually equation uses -k
x_0 = 0

We correct the last degree of the output when it degree sum is not even
*/

void generate_power_law_degree_dist(int nV, int k, int min_degree, int max_degree) {
	std::cout << 1 << " " << nV << std::endl;

	// X axis of power law, we are varying uniformly
	// y axis is change upto k_o to k degree
	// we take y sum diff to get exact degree for each of X
	double pre_sum_y = 0.0;
	double diff = 0.0;
	for (int X = min_degree; X <= max_degree; X++) {
		double numerator = (pow((double)X, k - 1.0) - 1.0)*pow(max_degree, k - 1.0);		// x_0 = 1
		double denumerator = (pow(max_degree, k - 1.0) - 1.0)*(pow((double)X, k - 1.0));	// x_1 = mv; x_0 = 0
		double y = numerator / denumerator;
		double current_y = y - pre_sum_y;

		double temp_res = current_y*nV + diff;
		int cur_nV = (int)(temp_res);
		diff = temp_res - (double) cur_nV;
		// if (X == max_degree && diff > 0.2)
			// cur_nV += 1;
		// for drawing appropriate graph
		// double cur_nV = current_y*nV;
		if (cur_nV) {
			for (int i = 0; i < cur_nV; i++) {
				std::cout << " " << X;
			}
		}
		pre_sum_y = y;
	}
	std::cout << std::endl;
}
