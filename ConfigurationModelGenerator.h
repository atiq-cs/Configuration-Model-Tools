// ConfigurationModelGenerator.h
#ifndef ConfigurationModelGenerator_H
#define ConfigurationModelGenerator_H

class RandomGraph;

// Class that handles all configuration model algorithms and required common properties
class ConfigurationModelGenerator {
private:
	std::vector<int> DegreeSequence;
	int degree_sum;

public:
	ConfigurationModelGenerator();
	~ConfigurationModelGenerator();
	void add_degree(int d);
	bool validate_input();
	void fix_degree_sequence();
	RandomGraph generate_graph();
	void print_graph(RandomGraph graph);
};

#endif
