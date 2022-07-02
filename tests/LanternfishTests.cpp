#include <iostream>
#include <ostream>
#define BOOST_TEST_MODULE LanternfishTests
#include <boost/test/unit_test.hpp>
#include "../prog/Lanternfish.hpp"

#include <istream>
#include <sstream>
#include <vector>
#include <string>

BOOST_AUTO_TEST_CASE(parse_input) {
    const std::string input = "3,4,3,1,2";
    std::istringstream is{input};
    std::istream &i = is ;
    std::vector<int> expected{3,4,3,1,2};

    auto fish = parseFish(i);

    BOOST_CHECK(fish == expected);
}

BOOST_AUTO_TEST_CASE(iterate_generation_no_spawn) {
    std::vector<int> fish{3,4,3,1,2};
    std::vector<int> expected{2,3,2,0,1};

    iterateGeneration(fish);

    BOOST_CHECK(fish == expected);
}

BOOST_AUTO_TEST_CASE(iterate_generation_spawn_one) {
    std::vector<int> fish{2,3,2,0,1};
    std::vector<int> expected{1,2,1,6,0,8};

    iterateGeneration(fish);

    BOOST_CHECK(fish == expected);
}

BOOST_AUTO_TEST_CASE(simulate_growth) {
    std::vector<int> fish{3,4,3,1,2};
    std::vector<int> expected{6,0,6,4,5,6,0,1,1,2,6,0,1,1,1,2,2,3,3,4,6,7,8,8,8,8};

    simulateGrowth(fish, 18);

    BOOST_CHECK(fish == expected);
}

BOOST_AUTO_TEST_CASE(answer_1) {
    const std::string input = "3,4,3,1,2";
    std::istringstream is{input};
    std::istream &i = is ;

    auto answer = answer1(i);
    std::cout << answer << std::endl;

    BOOST_CHECK(answer == 5934);
}
