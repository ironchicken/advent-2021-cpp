#include <iostream>
#include <ostream>
#define BOOST_TEST_MODULE LanternfishTests
#include <boost/test/unit_test.hpp>
#include "../prog/Lanternfish.hpp"

#include <istream>
#include <sstream>
#include <string>

bool isEqual(long (&a)[MAX_TIMER + 1], long (&b)[MAX_TIMER + 1]) {
    for (auto x = 0; x < MAX_TIMER + 1; x++) {
        if (a[x] != b[x]) {
            return false;
        }
    }
    return true;
}

BOOST_AUTO_TEST_CASE(parse_input) {
    const std::string input = "3,4,3,1,2";
    std::istringstream is{input};
    std::istream &i = is ;
    long fish[MAX_TIMER + 1];
    initFishMap(fish);
    long expected[MAX_TIMER + 1]{0,1,1,2,1,0,0,0,0};

    parseFish(fish, i);

    BOOST_CHECK(isEqual(fish, expected));
}

BOOST_AUTO_TEST_CASE(iterate_generation_no_spawn) {
    long fish[MAX_TIMER + 1]{0,1,1,2,1,0,0,0};
    long expected[MAX_TIMER + 1]{1,1,2,1,0,0,0,0,0};

    iterateGeneration(fish);

    BOOST_CHECK(isEqual(fish, expected));
}

BOOST_AUTO_TEST_CASE(iterate_generation_spawn_one) {
    long fish[MAX_TIMER + 1]{1,1,2,1,0,0,0,0};
    long expected[MAX_TIMER + 1]{1,2,1,0,0,0,1,0,1};

    iterateGeneration(fish);

    BOOST_CHECK(isEqual(fish, expected));
}

BOOST_AUTO_TEST_CASE(simulate_growth) {
    long fish[MAX_TIMER + 1]{0,1,1,2,1,0,0,0,0};
    long expected[MAX_TIMER + 1]{3,5,3,2,2,1,5,1,4};

    simulateGrowth(fish, 18);

    BOOST_CHECK(isEqual(fish, expected));
}

BOOST_AUTO_TEST_CASE(answer_1) {
    const std::string input = "3,4,3,1,2";
    std::istringstream is{input};
    std::istream &i = is ;

    auto answer = answer1(i);

    BOOST_CHECK(answer == 5934);
}

BOOST_AUTO_TEST_CASE(answer_2) {
    const std::string input = "3,4,3,1,2";
    std::istringstream is{input};
    std::istream &i = is ;

    auto answer = answer2(i);

    BOOST_CHECK(answer == 26984457539);
}
