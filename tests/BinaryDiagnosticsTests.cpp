#define BOOST_TEST_MODULE BinaryDiagnosticsTests
#include <boost/test/unit_test.hpp>
#include "../prog/BinaryDiagnostics.hpp"
#include <istream>
#include <sstream>
#include <vector>
#include <string>

BOOST_AUTO_TEST_CASE(tokenize_input) {
    const std::string input = "00100\n11110\n10110\n10111\n10101\n01111\n00111\n11100\n10000\n11001\n00010\n01010";
    std::istringstream is{input};
    std::istream &i = is ;
    std::vector<std::string> expected{
	"00100", "11110", "10110",
	"10111", "10101", "01111",
	"00111", "11100", "10000",
	"11001", "00010", "01010"};

    auto tokens = tokenize(i);

    BOOST_CHECK(tokens == expected);
}

BOOST_AUTO_TEST_CASE(gamma_rate) {
    std::vector<std::string> report {
	"00100", "11110", "10110",
	"10111", "10101", "01111",
	"00111", "11100", "10000",
	"11001", "00010", "01010"};

    BOOST_CHECK(gammaRate(report) == 22);
}

BOOST_AUTO_TEST_CASE(epsilon_rate) {
    std::vector<std::string> report {
	"00100", "11110", "10110",
	"10111", "10101", "01111",
	"00111", "11100", "10000",
	"11001", "00010", "01010"};

    BOOST_CHECK(epsilonRate(report) == 9);
}

BOOST_AUTO_TEST_CASE(power_consumption) {
    const std::string input = "00100\n11110\n10110\n10111\n10101\n01111\n00111\n11100\n10000\n11001\n00010\n01010";
    std::istringstream is{input};
    std::istream &i = is ;

  BOOST_CHECK(answer1(is) == 198);
}

BOOST_AUTO_TEST_CASE(oxygen_generator_rate) {
    std::vector<std::string> report {
	"00100", "11110", "10110",
	"10111", "10101", "01111",
	"00111", "11100", "10000",
	"11001", "00010", "01010"};

    BOOST_CHECK(oxygenGeneratorRate(report) == 23);
}

BOOST_AUTO_TEST_CASE(co2_scrubber_rate) {
    std::vector<std::string> report {
	"00100", "11110", "10110",
	"10111", "10101", "01111",
	"00111", "11100", "10000",
	"11001", "00010", "01010"};

    BOOST_CHECK(co2ScrubberRate(report) == 10);
}

BOOST_AUTO_TEST_CASE(life_support) {
    const std::string input = "00100\n11110\n10110\n10111\n10101\n01111\n00111\n11100\n10000\n11001\n00010\n01010";
    std::istringstream is{input};
    std::istream &i = is ;

  BOOST_CHECK(answer2(is) == 230);
}
