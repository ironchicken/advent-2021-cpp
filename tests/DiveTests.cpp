#define BOOST_TEST_MODULE DiveTests
#include <boost/test/unit_test.hpp>
#include "../prog/Dive.hpp"
#include <istream>
#include <sstream>
#include <vector>
#include <string>

BOOST_AUTO_TEST_CASE(tokenize_input) {
    const std::string input = "forward 5\ndown 5\nforward 8\nup 3\ndown 8\nforward 2";
    std::istringstream is{input};
    std::istream &i = is ;
    std::vector<std::string> expected {"forward", "5", "down", "5", "forward", "8", "up", "3", "down", "8", "forward", "2"};

    auto tokens = tokenize(i);

    BOOST_CHECK(tokens == expected);
}

BOOST_AUTO_TEST_CASE(parse_input) {
    const std::vector<std::string> input = {"forward", "5", "down", "5", "forward", "8", "up", "3", "down", "8", "forward", "2"};
    std::vector<Command> expected =
    {
	{Direction::Forward, 5},
	{Direction::Down, 5},
	{Direction::Forward, 8},
	{Direction::Up, 3},
	{Direction::Down, 8},
	{Direction::Forward, 2},
    };

    BOOST_CHECK(parse(input) == expected);
}

BOOST_AUTO_TEST_CASE(course_destination) {
    std::vector<Command> course =
    {
	{Direction::Forward, 5},
	{Direction::Down, 5},
	{Direction::Forward, 8},
	{Direction::Up, 3},
	{Direction::Down, 8},
	{Direction::Forward, 2},
    };
    Position expected{15, 10};
    const Position start = Position{0, 0};

    BOOST_CHECK(followCourse(start, course) == expected);
}

BOOST_AUTO_TEST_CASE(course_destination_with_aim_rules) {
    std::vector<Command> course =
    {
	{Direction::Forward, 5},
	{Direction::Down, 5},
	{Direction::Forward, 8},
	{Direction::Up, 3},
	{Direction::Down, 8},
	{Direction::Forward, 2},
    };

    const int expectedH = 15;
    const int expectedD = 60;
    const Aim start = Aim{0, 0, 0};

    auto destination = followAimCourse(start, course);

    BOOST_CHECK(destination.horizontal == expectedH && destination.depth == expectedD);
}
