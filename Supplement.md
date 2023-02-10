#### Earlier Drafts
**Main.cpp**  
This code block was previously in the beginning of main method. We don't implement iterations that way anymore!

```cpp
// generate sequence of degree, 1000 input
{
#ifdef FILE_IO
  std::ifstream inFile("iter-in.txt"); // input for this program
  if (inFile.good() == false)
  {
    std::cout << "File open for reading failed!! Exiting." << std::endl;
    return 0;
  }
  std::streambuf *cinbuf = std::cin.rdbuf(); // save old buf
  std::cin.rdbuf(inFile.rdbuf());         // redirect std::cin to inFile!

  std::ofstream outFile("ds-input.txt"); // output for this program
  if (inFile.good() == false)
  {
    std::cout << "File open for writing failed!! Exiting." << std::endl;
    return 0;
  }
  std::streambuf *coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(outFile.rdbuf());
#endif

  bool is_num_nodes_same, is_power_law, is_degree_same;
  int num_iterations, start_value, diff = 0, num_nodes;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  // Take each input line
  while (std::cin >> is_power_law >> is_num_nodes_same >> is_degree_same >> num_iterations >> num_nodes >>
       start_value)
  {
    // number of nodes same, degree varies
    if (is_num_nodes_same == true && is_degree_same == true)
    {
      for (int i = 0; i < num_iterations; i++)
      {
        std::cout << (int)is_power_law << " " << num_nodes << " " << start_value << std::endl;
      }
    }
    else if (is_num_nodes_same == true)
    {
      for (int value = start_value, i = 0; i < num_iterations; i++, value += diff)
      {
        std::cout << (int)is_power_law << " " << num_nodes << " " << value << std::endl;
      }
    }
    // number of degrees same, number of nodes varie
    else
    {
      // generate_uniform_degree_distribution(num_vertices, degree);
    }
  }

#ifdef FILE_IO
  std::cin.rdbuf(cinbuf);
  inFile.close();
  std::cout.rdbuf(coutbuf);
  outFile.close();
#endif
  // ref: http://en.cppreference.com/w/cpp/chrono/duration
  std::chrono::seconds file_IO_interval(2);
  // ref: http://en.cppreference.com/w/cpp/thread/sleep_for
  std::this_thread::sleep_for(file_IO_interval);
}
```
