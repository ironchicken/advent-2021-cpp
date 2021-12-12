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

std::pair<int, int> countBits(const std::vector<std::string> &numbers, int position) {
    int zeroCount { 0 };
    int oneCount { 0 };

    for (auto number : numbers) {
	auto bit = number[position];
	if (bit == '0') {
	    zeroCount += 1;
        } else if (bit == '1') {
	    oneCount += 1;
        }
    }

    return std::make_pair(zeroCount, oneCount);
}

template <class Func>
long rate(const std::vector<std::string> &report, Func compare) {
    std::vector<int> zeroCounts(MAX_NUMBER_WIDTH, 0);
    std::vector<int> oneCounts(MAX_NUMBER_WIDTH, 0);

    int numberWidth = report.front().length();

    for (int i = 0; i < numberWidth; i++) {
	auto counts = countBits(report, i);
	zeroCounts[i] += counts.first;
	oneCounts[i] += counts.second;
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

template <class Func>
long lifeSupportRate(const std::vector<std::string> &report, Func compare, char equalBit) {
    int position { 0 };
    std::vector<std::string> input = report;
    std::vector<std::string> filtered;

    while (input.size() > 1) {
	auto counts = countBits(input, position);
	if (compare(counts.first, counts.second)) {
          std::copy_if(input.begin(), input.end(),
                       std::back_inserter(filtered),
                       [position](std::string number) {
                         return number[position] == '0';
                       });
        } else if (compare(counts.second, counts.first)) {
          std::copy_if(input.begin(), input.end(),
                       std::back_inserter(filtered),
                       [position](std::string number) {
                         return number[position] == '1';
                       });
        } else if (counts.second == counts.first) {
          std::copy_if(input.begin(), input.end(),
                       std::back_inserter(filtered),
                       [position, equalBit](std::string number) {
                         return number[position] == equalBit;
                       });
        }
	input = filtered;
	filtered.clear();
	position++;
    }

    return std::stol(input.front(), nullptr, 2);
}

long oxygenGeneratorRate(const std::vector<std::string> &report) {
    return lifeSupportRate(report, std::greater<>(), '1');
}

long co2ScrubberRate(const std::vector<std::string> &report) {
    return lifeSupportRate(report, std::less<>(), '0');
}

long answer1(std::istream &in) {
    auto tokens = tokenize(in);
    auto gamma = gammaRate(tokens);
    auto epsilon = epsilonRate(tokens);

    return gamma * epsilon;
}

long answer2(std::istream &in) {
    auto tokens = tokenize(in);
    auto oxygen = oxygenGeneratorRate(tokens);
    auto co2 = co2ScrubberRate(tokens);

    return oxygen * co2;
}
