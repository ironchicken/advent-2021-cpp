#include <fstream>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include "SonarSweep.hpp"

const std::string input_file = "SonarSweep_input";

int main(int argc, char *argv[])
{
    std::vector<int> depths;
    std::ifstream input(input_file);

    if (input) {
	std::copy(std::istream_iterator<int>(input), std::istream_iterator<int>(),
		  std::back_inserter(depths));
    } else {
	std::cerr << "Couldn't open " << input_file << std::endl;
    }

    std::cout << "Part 1: " << answer1(depths) << std::endl;

    return 0;
}
