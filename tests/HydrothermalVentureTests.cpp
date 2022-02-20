#define BOOST_TEST_MODULE HydrothermalVentureTests
#include <boost/test/unit_test.hpp>
#include "../prog/HydrothermalVenture.hpp"

#include <istream>
#include <sstream>
#include <vector>
#include <string>

BOOST_AUTO_TEST_CASE(parse_line_segments) {
    const std::string input = "0,9 -> 5,9\n8,0 -> 0,8\n9,4 -> 3,4\n2,2 -> 2,1\n7,0 -> 7,4\n6,4 -> 2,0\n0,9 -> 2,9\n3,4 -> 1,4\n0,0 -> 8,8\n5,5 -> 8,2";
    std::istringstream is{input};
    std::istream &i = is ;
    std::vector<LineSegment> expected{
	LineSegment{Point{0, 9}, Point{5, 9}},
	LineSegment{Point{8, 0}, Point{0, 8}},
	LineSegment{Point{9, 4}, Point{3, 4}},
	LineSegment{Point{2, 2}, Point{2, 1}},
	LineSegment{Point{7, 0}, Point{7, 4}},
	LineSegment{Point{6, 4}, Point{2, 0}},
	LineSegment{Point{0, 9}, Point{2, 9}},
	LineSegment{Point{3, 4}, Point{1, 4}},
	LineSegment{Point{0, 0}, Point{8, 8}},
	LineSegment{Point{5, 5}, Point{8, 2}}
    };

    int width { 0 };
    int height { 0 };
    auto lineSegments = parseLineSegments(i, width, height);

    BOOST_CHECK(lineSegments == expected);
    BOOST_CHECK(width == 9);
    BOOST_CHECK(height == 9);
}

BOOST_AUTO_TEST_CASE(find_points_in_horizontal_forwards_line_segment) {
    LineSegment ls = {Point{0, 9}, Point{5, 9}};

    std::vector<Point> expected{Point{0, 9}, Point{1, 9}, Point{2, 9},
                                Point{3, 9}, Point{4, 9}, Point{5, 9}};

    auto points = findPoints(ls, false);

    BOOST_CHECK(points == expected);
}

BOOST_AUTO_TEST_CASE(find_points_in_horizontal_backwards_line_segment) {
    LineSegment ls = {Point{9, 4}, Point{3, 4}};

    std::vector<Point> expected{Point{9, 4}, Point{8, 4}, Point{7, 4},
	                        Point{6, 4}, Point{5, 4}, Point{4, 4},
				Point{3, 4}};

    auto points = findPoints(ls, false);

    BOOST_CHECK(points == expected);
}

BOOST_AUTO_TEST_CASE(find_points_in_vertical_upwards_line_segment) {
    LineSegment ls = {Point{0, 5}, Point{0, 0}};

    std::vector<Point> expected{Point{0, 5}, Point{0, 4}, Point{0, 3},
 	                        Point{0, 2}, Point{0, 1}, Point{0, 0}};

    auto points = findPoints(ls, false);

    BOOST_CHECK(points == expected);
}

BOOST_AUTO_TEST_CASE(find_points_in_vertical_downwards_line_segment) {
    LineSegment ls = {Point{0, 0}, Point{0, 5}};

    std::vector<Point> expected{Point{0, 0}, Point{0, 1}, Point{0, 2},
                                Point{0, 3}, Point{0, 4}, Point{0, 5}};

    auto points = findPoints(ls, false);

    BOOST_CHECK(points == expected);
}

BOOST_AUTO_TEST_CASE(find_points_in_forwards_downwards_diagonal_line_segment) {
    LineSegment ls = {Point{1, 1}, Point{3, 3}};

    std::vector<Point> expected{Point{1, 1}, Point{2, 2}, Point{3, 3}};

    auto points = findPoints(ls, true);

    BOOST_CHECK(points == expected);
}

BOOST_AUTO_TEST_CASE(find_points_in_forwards_upwards_diagonal_line_segment) {
    LineSegment ls = {Point{1, 3}, Point{3, 1}};

    std::vector<Point> expected{Point{1, 3}, Point{2, 2}, Point{3, 1}};

    auto points = findPoints(ls, true);

    BOOST_CHECK(points == expected);
}

BOOST_AUTO_TEST_CASE(find_points_in_backwards_downwards_diagonal_line_segment) {
    LineSegment ls = {Point{9, 7}, Point{7, 9}};

    std::vector<Point> expected{Point{9, 7}, Point{8, 8}, Point{7, 9}};

    auto points = findPoints(ls, true);

    BOOST_CHECK(points == expected);
}

BOOST_AUTO_TEST_CASE(find_points_in_backwards_upwards_diagonal_line_segment) {
    LineSegment ls = {Point{9, 9}, Point{7, 7}};

    std::vector<Point> expected{Point{9, 9}, Point{8, 8}, Point{7, 7}};

    auto points = findPoints(ls, true);

    BOOST_CHECK(points == expected);
}

BOOST_AUTO_TEST_CASE(add_lines_to_map) {
    LineSegment ls1 = {Point{0, 0}, Point{0, 5}};
    LineSegment ls2 = {Point{0, 0}, Point{5, 0}};

    Map map;

    addLinesToMap(std::vector<LineSegment>{ls1, ls2}, map, 6, 6, false);

    BOOST_CHECK(map[0][0] == 2 && map[0][1] == 1 && map[0][2] == 1 &&
                map[0][3] == 1 && map[0][4] == 1 && map[0][5] == 1 &&
                map[1][0] == 1 && map[2][0] == 1 && map[3][0] == 1 &&
                map[4][0] == 1 && map[5][0] == 1);
}

BOOST_AUTO_TEST_CASE(count_overlaps) {
    LineSegment ls1 = {Point{0, 0}, Point{0, 5}};
    LineSegment ls2 = {Point{0, 0}, Point{5, 0}};

    Map map;

    addLinesToMap(std::vector<LineSegment>{ls1, ls2}, map, 6, 6, false);

    BOOST_CHECK(countOverlaps(map) == 1);
}

BOOST_AUTO_TEST_CASE(find_overlaps_in_input) {
    const std::string input = "0,9 -> 5,9\n8,0 -> 0,8\n9,4 -> 3,4\n2,2 -> 2,1\n7,0 -> 7,4\n6,4 -> 2,0\n0,9 -> 2,9\n3,4 -> 1,4\n0,0 -> 8,8\n5,5 -> 8,2";
    std::istringstream is{input};
    std::istream &i = is;

    BOOST_CHECK(answer1(i) == 5);
}

BOOST_AUTO_TEST_CASE(find_overlaps_in_input_with_diagonals) {
    const std::string input = "0,9 -> 5,9\n8,0 -> 0,8\n9,4 -> 3,4\n2,2 -> 2,1\n7,0 -> 7,4\n6,4 -> 2,0\n0,9 -> 2,9\n3,4 -> 1,4\n0,0 -> 8,8\n5,5 -> 8,2";
    std::istringstream is{input};
    std::istream &i = is;

    BOOST_CHECK(answer2(i) == 12);
}
