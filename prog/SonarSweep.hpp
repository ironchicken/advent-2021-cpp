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

int answer2(std::vector<int> in) {
    int increases { 0 };

    auto i1 = in.begin();
    auto i2 = in.begin();
    auto i3 = in.begin();

    i2++;
    i3++; i3++;

    int prev { *i1 + *i2 + *i3 };

    i1++; i2++; i3++;

    while (i3 != in.end()) {
	int windowDepth { *i1 + *i2 + *i3 };
        if (windowDepth > prev) {
	    increases++;
        }
        prev = windowDepth;
        i1++;
        i2++;
        i3++;
    }

    return increases;
}
