#include <vector>

int answer1(std::vector<int> in) {
    int increases { 0 };
    auto it = in.begin();
    int prev {*it};
    it++;

    while (it != in.end()) {
	auto depth = *it;
        if (depth > prev) {
          increases++;
        }
        prev = depth;
	it++;
    }

    return increases;
}
