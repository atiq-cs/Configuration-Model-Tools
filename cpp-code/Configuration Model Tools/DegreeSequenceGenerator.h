// DegreeSequenceGenerator.h
#ifndef DegreeSequenceGenerator_H
#define DegreeSequenceGenerator_H

void generate_uniform_degree_distribution(int nV, int degree);
// deprecated
//void generate_power_law_degree_distribution(int nV, int min_degree, int max_degree);
void generate_power_law_degree_distribution_norm(int nV, int min_degree, int max_degree);

#endif
