#include <fstream>
#include <iostream>
#include <string>
#include "Lanternfish.hpp"

const std::string input_file = "Lanternfish_input";

int main(int argc, char *argv[])
{
    std::ifstream input(input_file);
    std::istream& is = input;

    std::cout << "Part 1: " << answer1(is) << std::endl;

    return 0;
}
