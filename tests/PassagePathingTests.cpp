#define BOOST_TEST_MODULE PassagePathingTests
#include <boost/test/unit_test.hpp>
#include "../prog/PassagePathing.hpp"
#include <istream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

BOOST_AUTO_TEST_CASE(isUpper_lower_case) {
    std::string lower = "lower";

    BOOST_TEST(isUpper(lower) == false);
}

BOOST_AUTO_TEST_CASE(isUpper_upper_case) {
    std::string upper = "UPPER";

    BOOST_TEST(isUpper(upper) == true);
}

BOOST_AUTO_TEST_CASE(isUpper_mixed_case) {
    std::string mixed = "Mixed";

    BOOST_TEST(isUpper(mixed) == false);
}

BOOST_AUTO_TEST_CASE(parse_node_start) {
    std::string start = "start";
    Node expected { NodeType::Start, "" };

    BOOST_TEST(parseToken(start) == expected);
}

BOOST_AUTO_TEST_CASE(parse_node_end) {
    std::string end = "end";
    Node expected { NodeType::End, "" };

    BOOST_TEST(parseToken(end) == expected);
}

BOOST_AUTO_TEST_CASE(parse_node_large) {
    std::string large = "AA";
    Node expected { NodeType::Large, "AA" };

    BOOST_TEST(parseToken(large) == expected);
}

BOOST_AUTO_TEST_CASE(parse_node_small) {
    std::string small = "aa";
    Node expected { NodeType::Small, "aa" };

    BOOST_TEST(parseToken(small) == expected);
}

BOOST_AUTO_TEST_CASE(parse_map) {
    const std::string input = "start-A\nstart-b\nA-c\nA-b\nb-d\nA-end\nb-end";
    std::istringstream is{input};
    std::istream &i = is;

    Map expected{
        std::make_pair(Node{NodeType::Start, ""}, Node{NodeType::Large, "A"}),
        std::make_pair(Node{NodeType::Start, ""}, Node{NodeType::Small, "b"}),
        std::make_pair(Node{NodeType::Large, "A"}, Node{NodeType::Small, "c"}),
        std::make_pair(Node{NodeType::Large, "A"}, Node{NodeType::Small, "b"}),
        std::make_pair(Node{NodeType::Small, "b"}, Node{NodeType::Small, "d"}),
        std::make_pair(Node{NodeType::Large, "A"}, Node{NodeType::End, ""}),
        std::make_pair(Node{NodeType::Small, "b"}, Node{NodeType::End, ""}),
    };

    BOOST_TEST(parseMap(tokenize(i)) == expected);
}
