//
// PURPOSE: Random Graph Generator Driver Program (Configuration Model Tools)
//
// Author : Atiq Rahman
// Date   : 04-20-2015
// Status : 
// Remarks: Take a set of input degree sequence and generate a random graph
//    with same set of degree sequence for each of the vertex
//    Terminates when input 0 is encountered for nunber of vertices
//    Demos:
//     - standard cpp
// Output :
//


#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include "DegreeSequenceGenerator.h"
#include "ConfigurationModelGenerator.h"
#include "RandomGraph.h"

#define FILE_IO  TRUE

// My own file template for C++
#ifdef FILE_IO
#include <fstream>
#endif


int main() {
  // First stage: Generate degree sequence
  bool graph_generation_enabled = true;
  {
#ifdef FILE_IO
    // reason why file open might fail in MAC OS X, had to change working directory ref:
    // http://stackoverflow.com/questions/14476655/code-runs-perfect-in-g-but-not-in-xcode-cannot-find-file/14478210#14478210

    std::ifstream inFile("ds-input.txt");  // input for this program
    if (inFile.good() == false) {
      std::cout << "File open for reading failed!! Exiting." << std::endl;
      return 0;
    }
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(inFile.rdbuf()); //redirect std::cin to inFile!

    std::ofstream outFile("ds-output.txt");  // output for this program
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
    while (std::cin >> num_vertices >> degree >> is_power_law) {
      // Code for power law degree distribution
      if (is_power_law == true) {
        generate_power_law_degree_dist(num_vertices, 2, 1, degree);
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
  }


  // Second stage: intermediate pipeline
  {
    // ref: http://en.cppreference.com/w/cpp/chrono/duration
    std::chrono::seconds file_IO_interval(1);
    // ref: http://en.cppreference.com/w/cpp/thread/sleep_for
    std::this_thread::sleep_for(file_IO_interval);

    /* // wait for fixing file
    {
      int test = 0;
      std::cout << "press a key to fix last degree...";
      std::cin >> test;
    }*/

#ifdef FILE_IO
    // reason why file open might fail in MAC OS X, had to change working directory ref:
    // http://stackoverflow.com/questions/14476655/code-runs-perfect-in-g-but-not-in-xcode-cannot-find-file/14478210#14478210

    std::ifstream inFile("ds-output.txt");  // input for this program
    if (inFile.good() == false) {
      std::cout << "File open for reading failed!! Exiting." << std::endl;
      return 0;
    }
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(inFile.rdbuf()); //redirect std::cin to inFile!

    std::ofstream outFile("cf-input.txt");  // output for this program
    if (inFile.good() == false) {
      std::cout << "File open for writing failed!! Exiting." << std::endl;
      return 0;
    }
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(outFile.rdbuf());
#endif
    bool is_power_law;
    int num_vertices;
    int num_iterations = 1; // 2000;  // 1 = repeatation disabled

    while (std::cin >> is_power_law >> num_vertices) {
      std::vector<int> degree_list(num_vertices);
      degree_list.clear();

      int degree;
      // take line input and counter number of items
      std::string line;

      std::getline(std::cin, line);
      std::getline(std::cin, line);
      std::istringstream iss(line);
      while (iss >> degree) {
        degree_list.push_back(degree);
      }

      if (is_power_law) {
        int diff = (int)abs((int)(degree_list.size() - num_vertices));
        if (diff > 0) {
          std::cerr << "For " << num_vertices << " max degree " << degree_list[degree_list.size()-1] << " vertices lost: " << diff << \
            std::endl;
        }
        else {
          for (int q = 0; q < num_iterations; q++) {
            std::cout << (int)is_power_law << " " << degree_list.size() << std::endl;

            // reverse degree sequence for proper graph plotting of power law where long tail
            // appears on the right side
						for (int i = degree_list.size()-1; i>=0; i--)
							std::cout << " " << degree_list[i];

            std::cout << std::endl;
          }
        }
      }
      else { 
        std::cout << (int) is_power_law << " " << degree_list.size() << std::endl;

        for (int i = 0; i < degree_list.size(); i++) {
          std::cout << " " << degree_list[i];
        }
        std::cout << std::endl;
      }
    }
#ifdef FILE_IO
    std::cin.rdbuf(cinbuf);
    inFile.close();
    std::cout.rdbuf(coutbuf);
    outFile.close();
#endif
  }


  // 3rd Stage: Random Graph Generator
  if (graph_generation_enabled)
  {
    // sleep 1 second waiting for file IO to be complete
    // ref: http://en.cppreference.com/w/cpp/chrono/duration
    std::chrono::seconds file_IO_interval(1);
    // ref: http://en.cppreference.com/w/cpp/thread/sleep_for
    std::this_thread::sleep_for(file_IO_interval);

    // Open file
#ifdef FILE_IO
    std::ifstream inFile("cf-input.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(inFile.rdbuf()); //redirect std::cin to inFile!

    std::ofstream outFile("cf-output.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(outFile.rdbuf());
#endif

    int num_vertices = 0;
    bool is_power_law = false;
		int seq = 1;

    while (std::cin >> is_power_law >> num_vertices && num_vertices) {
			seq++;
			if (seq%50 == 0)
				std::cerr << "\rProcessing graph "<< seq;

      std::cout << num_vertices;
      ConfigurationModelGenerator modelgenerator;

      int degree = 0;
      // add input degree sequence to ConfigurationModelGenerator
      for (int i = 0; i < num_vertices; i++) {
        std::cin >> degree;
        modelgenerator.add_degree(degree);
        if (is_power_law) {
          // std::cout << " " << degree;
          if (i == num_vertices-1)
            std::cout << " " << degree << std::endl;;
        }
        else if (i == 0)
          std::cout << " " << degree << std::endl;;
          
      }
      // if (is_power_law)
        // std::cout << std::endl;;

      modelgenerator.fix_degree_sequence();

      RandomGraph randomgraph = modelgenerator.generate_graph();
      randomgraph.sort_edges();
      modelgenerator.print_graph(randomgraph);
    }

    std::cerr << std::endl;

#ifdef FILE_IO
    std::cin.rdbuf(cinbuf);
    inFile.close();
    std::cout.rdbuf(coutbuf);
    outFile.close();
#endif
  }
  return 0;
}
