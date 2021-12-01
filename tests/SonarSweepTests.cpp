#define BOOST_TEST_MODULE SonarSweepTests
#include <boost/test/unit_test.hpp>
#include "../prog/SonarSweep.hpp"
#include <vector>

BOOST_AUTO_TEST_CASE(depth_increases) {
    const std::vector<int> test_input = {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};
    BOOST_CHECK(answer1(test_input) == 7);
}
