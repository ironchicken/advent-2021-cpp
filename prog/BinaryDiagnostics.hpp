#include <sstream>
#include <algorithm>
#include <istream>
#include <iterator>
#include <string>
#include <vector>
#include <sstream>

constexpr int MAX_NUMBER_WIDTH = 12;

std::vector<std::string> tokenize(std::istream &in) {
    std::vector<std::string> tokens;

    std::copy(std::istream_iterator<std::string>(in),
	      std::istream_iterator<std::string>(), std::back_inserter(tokens));

    return tokens;
}

template<class Func>
long rate(const std::vector<std::string> &report, Func compare) {
    std::vector<int> zeroCounts(MAX_NUMBER_WIDTH, 0);
    std::vector<int> oneCounts(MAX_NUMBER_WIDTH, 0);
    int bitPosition { 0 };
    int numberWidth { 0 };

    for (auto number : report) {
	for (auto bit : number) {
	    if (bit == '0') {
		zeroCounts[bitPosition] += 1;
	    } else if (bit == '1') {
		oneCounts[bitPosition] += 1;
	    }
	    bitPosition++;
        }
	numberWidth = bitPosition;
        bitPosition = 0;
    }

    std::string rate;

    for (int i = 0; i < numberWidth; i++) {
	if (compare(zeroCounts[i], oneCounts[i])) { // greater than
	    rate += '0';
	} else if (compare(oneCounts[i], zeroCounts[i])) {
	    rate += '1';
	} else {
	    throw "1 and 0 counts are equal";
	}
    }

    return std::stol(rate, nullptr, 2);
}

long gammaRate(const std::vector<std::string> &report) {
    return rate(report, std::greater<>());
}

long epsilonRate(const std::vector<std::string> &report) {
    return rate(report, std::less<>());
}

long oxygenGeneratorRate(const std::vector<std::string> &report) { return 0; }

long co2ScrubberRate(const std::vector<std::string> &report) { return 0; }

long answer1(std::istream &in) {
    auto tokens = tokenize(in);
    auto gamma = gammaRate(tokens);
    auto epsilon = epsilonRate(tokens);

    return gamma * epsilon;
}
