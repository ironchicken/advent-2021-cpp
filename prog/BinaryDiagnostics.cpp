#include <fstream>
#include <iostream>
#include <string>
#include "BinaryDiagnostics.hpp"

const std::string input_file = "BinaryDiagnostics_input";

int main(int argc, char *argv[])
{
    std::ifstream input(input_file);
    std::istream& is = input;

    std::cout << "Part 1: " << answer1(is) << std::endl;

    return 0;
}
