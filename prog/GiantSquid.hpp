#include <iterator>
#include <istream>
#include <optional>
#include <string>
#include <utility>
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

using MarkedBoard = std::vector<bool>;

void initMarks(const std::vector<Board>& boards, std::vector<MarkedBoard>& marks) {
    for (int i { 0 }; i < boards.size(); i++) {
	marks.emplace_back(std::vector(BOARD_WIDTH * BOARD_HEIGHT, false));
    }
}

void markBoards(int called, const std::vector<Board>& boards, std::vector<MarkedBoard>& marks) {
    auto boardIt = boards.begin();
    auto markIt = marks.begin();

    while (boardIt != boards.end()) {
	int i { 0 };
	for (auto n : *boardIt) {
	    if (n == called) {
		(*markIt)[i] = true;
	    }
	    i++;
        }
	boardIt++;
	markIt++;
    }
}

template <typename T>
std::vector<T> boardRow(int y, const std::vector<T>& grid) {
    std::vector<T> row;
    y = y * BOARD_HEIGHT;

    for (int i { 0 }; i < BOARD_WIDTH; i++) {
	row.push_back(grid[y + i]);
    }

    return row;
}

template <typename T>
std::vector<T> boardColumn(int x, const std::vector<T>& grid) {
    std::vector<T> column;

    for (int i { 0 }; i < BOARD_HEIGHT; i++) {
	column.push_back(grid[i * BOARD_WIDTH + x]);
    }

    return column;
}

int encodeWin(int call, const Board &board, const MarkedBoard &marked) {
    auto boardIt = board.begin();
    auto markIt = marked.begin();

    int sum { 0 };

    while (boardIt != board.end()) {
	if (*markIt == false) {
	    sum += *boardIt;
	}
	boardIt++;
	markIt++;
    }

    return sum * call;
}

const std::vector<bool> winningRow = std::vector(BOARD_WIDTH, true);
const std::vector<bool> winningCol = std::vector(BOARD_HEIGHT, true);

std::optional<int> checkWinner(int call, const std::vector<Board>& boards, const std::vector<MarkedBoard>& marks) {
    auto boardIt = boards.begin();
    auto markIt = marks.begin();

    while (markIt != marks.end()) {
	for (int y { 0 }; y < BOARD_WIDTH; y++) {
	    auto row = boardRow(y, *markIt);
            if (row == winningRow) {
		return encodeWin(call, *boardIt, *markIt);
            }
        }
	for (int x { 0 }; x < BOARD_HEIGHT; x++) {
	    auto col = boardColumn(x, *markIt);
            if (col == winningCol) {
		return encodeWin(call, *boardIt, *markIt);
            }
        }
        markIt++;
        boardIt++;
    }

    return std::nullopt;
}

int playToWin(const std::vector<int>& calls, const std::vector<Board>& boards, std::vector<MarkedBoard>& marks) {
    for (auto call : calls) {
	markBoards(call, boards, marks);
	auto winner = checkWinner(call, boards, marks);
        if (winner.has_value()) {
	    return winner.value();
        }
    }

    throw "No winner found";
}

bool alreadyWon(int i, const std::vector<std::pair<int, int>>& winners) {
    for (auto w : winners) {
	if (w.first == i) {
	    return true;
	}
    }
    return false;
}

void findWinners(int call, const std::vector<Board>& boards, const std::vector<MarkedBoard>& marks, std::vector<std::pair<int, int>>& winners) {
    auto boardIt = boards.begin();
    auto markIt = marks.begin();

    int i { 0 };

    while (markIt != marks.end()) {
	if (!alreadyWon(i, winners)) {
	    for (int y { 0 }; y < BOARD_WIDTH; y++) {
		auto row = boardRow(y, *markIt);
		if (row == winningRow) {
		    winners.emplace_back(std::make_pair(i, encodeWin(call, *boardIt, *markIt)));
		}
	    }
	    for (int x { 0 }; x < BOARD_HEIGHT; x++) {
		auto col = boardColumn(x, *markIt);
                if (col == winningCol) {
		    winners.emplace_back(std::make_pair(i, encodeWin(call, *boardIt, *markIt)));
                }
            }
        }
        markIt++;
        boardIt++;
	i++;
    }
}

int playToLose(const std::vector<int>& calls, const std::vector<Board>& boards, std::vector<MarkedBoard>& marks, std::vector<std::pair<int, int>>& winners) {
    for (auto call : calls) {
	markBoards(call, boards, marks);
	findWinners(call, boards, marks, winners);
    }

    return winners.back().second;
}

int answer1(std::istream &in) {
    auto calls = parseCalls(in);
    auto boards = parseBoards(in);

    std::vector<MarkedBoard> marks;
    initMarks(boards, marks);

    return playToWin(calls, boards, marks);
}


int answer2(std::istream &in) {
    auto calls = parseCalls(in);
    auto boards = parseBoards(in);

    std::vector<MarkedBoard> marks;
    initMarks(boards, marks);
    std::vector<std::pair<int, int>> winners;

    return playToLose(calls, boards, marks, winners);
}
