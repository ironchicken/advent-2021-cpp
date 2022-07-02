#include <istream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> parseFish(std::istream& in) {
    char delimiter = ',';
    std::string number;
    std::vector<int> numbers;

    while (std::getline(in, number, delimiter)) {
        numbers.push_back(std::stoi(number));
    }

    return numbers;
}

void iterateGeneration(std::vector<int> &fish) {
    auto length = fish.size();

    for (auto i = 0; i < length; i++) {
        auto f = fish[i];
        if (f > 0) {
            fish[i]--;
        }
        if (f == 0) {
            fish[i] = 6;
            fish.push_back(8);
        }
    }
}

void simulateGrowth(std::vector<int> &fish, const int days) {
    for (int i = 0; i < days; i++) {
        iterateGeneration(fish);
    }
}

int answer1(std::istream& in) {
    auto fish = parseFish(in);
    simulateGrowth(fish, 80);

    return fish.size();
}
