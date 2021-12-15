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
