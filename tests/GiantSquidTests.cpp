#define BOOST_TEST_MODULE BinaryDiagnosticsTests
#include <boost/test/unit_test.hpp>
#include "../prog/GiantSquid.hpp"
#include <istream>
#include <sstream>
#include <vector>
#include <string>

BOOST_AUTO_TEST_CASE(parse_calls_from_input) {
  const std::string input{
      "7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1"};
  std::istringstream is{input};
  std::istream &i = is;
  std::vector<int> expected{7,  4,  9,  5,  11, 17, 23, 2,  0,
                            14, 21, 24, 10, 16, 13, 6,  15, 25,
                            12, 22, 18, 20, 8,  19, 3,  26, 1};

  auto calls = parseCalls(i);

  BOOST_CHECK(calls == expected);
}

BOOST_AUTO_TEST_CASE(parse_boards_from_input) {
    const std::string input{
	"22 13 17 11  0\n 8  2 23  4 24\n21  9 14 16  7\n 6 10  3 18  5\n 1 12 "
	"20 15 19\n\n 3 15  0  2 22\n 9 18 13 17  5\n19  8  7 25 23\n20 11 10 24 "
	" 4\n14 21 16 12  6\n\n14 21 17 24  4\n10 16 15  9 19\n18  8 23 26 "
	"20\n22 11 13  6  5\n 2  0 12  3  7"};
    std::istringstream is{input};
    std::istream &i = is;

    std::vector<Board> expected{
        {22, 13, 17, 11, 0, 8,  2, 23, 4,  24, 21, 9, 14,
         16, 7,  6,  10, 3, 18, 5, 1,  12, 20, 15, 19},
        {3,  15, 0,  2,  22, 9,  18, 13, 17, 5,  19, 8, 7,
         25, 23, 20, 11, 10, 24, 4,  14, 21, 16, 12, 6},
        {14, 21, 17, 24, 4,  10, 16, 15, 9, 19, 18, 8, 23,
         26, 20, 22, 11, 13, 6,  5,  2,  0, 12, 3,  7}};

    auto boards = parseBoards(i);

    BOOST_CHECK(boards == expected);
}

BOOST_AUTO_TEST_CASE(mark_boards) {
    std::vector<Board> boards{
	{22, 13, 17, 11, 0, 8,  2, 23, 4,  24, 21, 9, 14,
	 16, 7,  6,  10, 3, 18, 5, 1,  12, 20, 15, 19},
	{3,  15, 0,  2,  22, 9,  18, 13, 17, 5,  19, 8, 7,
	 25, 23, 20, 11, 10, 24, 4,  14, 21, 16, 12, 6},
	{14, 21, 17, 24, 4,  10, 16, 15, 9, 19, 18, 8, 23,
	 26, 20, 22, 11, 13, 6,  5,  2,  0, 12, 3,  7}};

    std::vector<MarkedBoard> marks;
    std::vector<MarkedBoard> expected{
	{false, false, false, false, false, false,  false, false, false,  false, false, false, false,
	 false, true,  false,  false, false, false, false, false,  false, false, false, false},
	{false,  false, false,  false,  false, false,  false, false, false, false,  false, false, true,
	 false, false, false, false, false, false, false,  false, false, false, false, false},
	{false, false, false, false, false,  false, false, false, false, false, false, false, false,
	 false, false, false, false, false, false,  false,  false,  false, false, false,  true}};


    initMarks(boards, marks);
    markBoards(7, boards, marks);

    BOOST_CHECK(marks == expected);
}

BOOST_AUTO_TEST_CASE(encode_win) {
    Board board {14, 21, 17, 24, 4,  10, 16, 15, 9, 19, 18, 8, 23,
	 26, 20, 22, 11, 13, 6,  5,  2,  0, 12, 3,  7};
    MarkedBoard marked{true,  true,  true,  true,  true,  false, false,
                       false, true,  false, false, false, true,  false,
                       false, false, true,  false, false, true,  true,
                       true,  false, false, true};

    auto win = encodeWin(24, board, marked);

    BOOST_CHECK(win == 4512);
}

BOOST_AUTO_TEST_CASE(board_row) {
      std::vector<Board> boards{
          {22, 13, 17, 11, 0, 8,  2, 23, 4,  24, 21, 9, 14,
           16, 7,  6,  10, 3, 18, 5, 1,  12, 20, 15, 19},
          {3,  15, 0,  2,  22, 9,  18, 13, 17, 5,  19, 8, 7,
           25, 23, 20, 11, 10, 24, 4,  14, 21, 16, 12, 6},
          {14, 21, 17, 24, 4,  10, 16, 15, 9, 19, 18, 8, 23,
           26, 20, 22, 11, 13, 6,  5,  2,  0, 12, 3,  7}};

      std::vector<int> expected = {21, 9, 14, 16, 7};

      auto row = boardRow(2, boards[0]);

      BOOST_CHECK(row == expected);
    }

BOOST_AUTO_TEST_CASE(board_column) {
    std::vector<Board> boards{
	{22, 13, 17, 11, 0, 8,  2, 23, 4,  24, 21, 9, 14,
	 16, 7,  6,  10, 3, 18, 5, 1,  12, 20, 15, 19},
	{3,  15, 0,  2,  22, 9,  18, 13, 17, 5,  19, 8, 7,
	 25, 23, 20, 11, 10, 24, 4,  14, 21, 16, 12, 6},
	{14, 21, 17, 24, 4,  10, 16, 15, 9, 19, 18, 8, 23,
	 26, 20, 22, 11, 13, 6,  5,  2,  0, 12, 3,  7}};

    std::vector<int> expected = {17, 23, 14, 3, 20};

    auto column = boardColumn(2, boards[0]);

    BOOST_CHECK(column == expected);
}

BOOST_AUTO_TEST_CASE(play_to_win_bingo) {
    std::vector<int> calls{7,  4,  9,  5,  11, 17, 23, 2,  0,
	14, 21, 24, 10, 16, 13, 6,  15, 25,
	12, 22, 18, 20, 8,  19, 3,  26, 1};

    std::vector<Board> boards{
	{22, 13, 17, 11, 0, 8,  2, 23, 4,  24, 21, 9, 14,
	 16, 7,  6,  10, 3, 18, 5, 1,  12, 20, 15, 19},
	{3,  15, 0,  2,  22, 9,  18, 13, 17, 5,  19, 8, 7,
	 25, 23, 20, 11, 10, 24, 4,  14, 21, 16, 12, 6},
	{14, 21, 17, 24, 4,  10, 16, 15, 9, 19, 18, 8, 23,
	 26, 20, 22, 11, 13, 6,  5,  2,  0, 12, 3,  7}};

    std::vector<MarkedBoard> marks;
    initMarks(boards, marks);

    auto winner = playToWin(calls, boards, marks);

    BOOST_CHECK(winner == 4512);
}

BOOST_AUTO_TEST_CASE(play_to_lose_bingo) {
    std::vector<int> calls{7,  4,  9,  5,  11, 17, 23, 2,  0,
	14, 21, 24, 10, 16, 13, 6,  15, 25,
	12, 22, 18, 20, 8,  19, 3,  26, 1};

    std::vector<Board> boards{
	{22, 13, 17, 11, 0, 8,  2, 23, 4,  24, 21, 9, 14,
	 16, 7,  6,  10, 3, 18, 5, 1,  12, 20, 15, 19},
	{3,  15, 0,  2,  22, 9,  18, 13, 17, 5,  19, 8, 7,
	 25, 23, 20, 11, 10, 24, 4,  14, 21, 16, 12, 6},
	{14, 21, 17, 24, 4,  10, 16, 15, 9, 19, 18, 8, 23,
	 26, 20, 22, 11, 13, 6,  5,  2,  0, 12, 3,  7}};

    std::vector<MarkedBoard> marks;
    initMarks(boards, marks);
    std::vector<std::pair<int, int>> winners;

    auto winner = playToLose(calls, boards, marks, winners);

    BOOST_CHECK(winner == 1924);
}

BOOST_AUTO_TEST_CASE(test_answer1) {
    const std::string input{
      "7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1\n\n"
      "22 13 17 11  0\n 8  2 23  4 24\n21  9 14 16  7\n 6 10  3 18  5\n 1 12 "
      "20 15 19\n\n 3 15  0  2 22\n 9 18 13 17  5\n19  8  7 25 23\n20 11 10 24 "
      " 4\n14 21 16 12  6\n\n14 21 17 24  4\n10 16 15  9 19\n18  8 23 26 "
      "20\n22 11 13  6  5\n 2  0 12  3  7"};

    std::istringstream is{input};
    std::istream &i = is;

    BOOST_CHECK(answer1(i) == 4512);
}

BOOST_AUTO_TEST_CASE(test_answer2) {
    const std::string input{
      "7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1\n\n"
      "22 13 17 11  0\n 8  2 23  4 24\n21  9 14 16  7\n 6 10  3 18  5\n 1 12 "
      "20 15 19\n\n 3 15  0  2 22\n 9 18 13 17  5\n19  8  7 25 23\n20 11 10 24 "
      " 4\n14 21 16 12  6\n\n14 21 17 24  4\n10 16 15  9 19\n18  8 23 26 "
      "20\n22 11 13  6  5\n 2  0 12  3  7"};

    std::istringstream is{input};
    std::istream &i = is;

    BOOST_CHECK(answer2(i) == 1924);
}
