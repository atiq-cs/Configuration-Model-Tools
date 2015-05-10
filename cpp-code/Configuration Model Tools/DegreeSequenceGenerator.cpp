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
	double k = 6;
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

/*
	Power law degree distribution implementation
	Does normalization as well
*/
void generate_power_law_degree_distribution_norm(int nV, int min_degree, int max_degree) {
	/* Verify degree code block removed
	reason: we correct the last degree of the output when it degree sum is not even
	} */

	// std::cout << 1 << " " << nV << std::endl;

	// power law formula test
	double d_max = max_degree;		// x_1
	double d_min = min_degree;		// x_0
	double k = 3;
	double k_prime = k+1;

	//double y = 0.1;
	int vert_var = (int)ceil(sqrt(1 + 8 * nV) / 2.0 - 0.5);
	double y_uniform = 1.00 / vert_var;

	//int X = (int) pow(pow_res, 1.00 / k_prime);
	// double X = pow(pow_res, 1.00 / k_prime);
	// std::cout << "power law output: " << X << std::endl;

	int i = vert_var;
	std::cout << 1 << " " << (int)(vert_var*(vert_var + 1) / 2.0) << std::endl;
	int degree_sum = 0;
	int vert_sum = 0;
	// for (double x = min_x; x < max_x + 2 * std::numeric_limits<double>::epsilon(); x += interval_x; i++) {
	for (double y = 1; i>=1; y -= y_uniform, i--) {
		double pow_res_max = pow(d_max, k_prime);
		double pow_res_min = pow(d_min, k_prime);
		double pow_res = (pow_res_max - pow_res_min) * y + pow_res_min;
		double X = pow(pow_res, 1.00 / k_prime);
		int degree = max_degree-(int) X;
		degree_sum += degree;
		if (i == nV - 1 && degree_sum % 2) {
			// std::cout << " degree correction for configuration model." << std::endl;
			X += 1;
		}
		/*
		for (int j = 0; j < i; j++)
			std::cout << degree << " ";*/
		std::cout << i << "," << degree << std::endl;
		vert_sum += i;
		// std::cout << " got sum " << vert_sum << " ";
	}


	// end the file with a new line
	std::cout << std::endl;
}
