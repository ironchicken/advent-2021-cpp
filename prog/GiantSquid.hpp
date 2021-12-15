#include <iterator>
#include <istream>
#include <string>
#include <vector>

constexpr int BOARD_WIDTH = 5;
constexpr int BOARD_HEIGHT = 5;

std::vector<int> parseCalls(std::istream& in) {
    std::vector<int> calls;

    std::string callsLine;
    std::getline(in, callsLine);

    auto start { 0U };
    auto end = callsLine.find(',');

    while (end != std::string::npos) {
	calls.push_back(std::stoi(callsLine.substr(start, end - start)));
	start = end + 1;
	end = callsLine.find(',', start);
    }

    calls.push_back(std::stoi(callsLine.substr(start)));

    return calls;
}

using Board = std::vector<int>;

std::vector<Board> parseBoards(std::istream &in) {
    std::vector<Board> boards;

    std::vector<std::string> tokens;

    std::copy(std::istream_iterator<std::string>(in),
	      std::istream_iterator<std::string>(), std::back_inserter(tokens));

    auto i { 0U };
    Board b {};

    for (auto t : tokens) {
	if (i > 0 && i % (BOARD_WIDTH * BOARD_HEIGHT) == 0) {
	    boards.push_back(b);
	    b.clear();
	}
	b.push_back(std::stoi(t));
	i++;
    }

    boards.push_back(b);

    return boards;
}
