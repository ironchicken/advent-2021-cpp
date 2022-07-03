#include <istream>
#include <sstream>
#include <string>

constexpr int MAX_TIMER = 8;
constexpr int NEW_TIMER = 6;

void initFishMap(long (&fish)[MAX_TIMER + 1]) {
    for (auto i = 0; i < MAX_TIMER + 1; i++) {
        fish[i] = 0;
    }
}

void parseFish(long (&fish)[MAX_TIMER + 1], std::istream& in) {
    char delimiter = ',';
    std::string number;

    while (std::getline(in, number, delimiter)) {
        fish[std::stoi(number)]++;
    }
}

void iterateGeneration(long (&fish)[MAX_TIMER + 1]) {
    long nextGen[MAX_TIMER + 1];
    initFishMap(nextGen);

    for (auto i = 0; i < MAX_TIMER; i++) {
        nextGen[i] = fish[i + 1];
    }
    if (fish[0] > 0) {
        nextGen[MAX_TIMER] += fish[0];
        nextGen[NEW_TIMER] += fish[0];
    }

    for (auto i = 0; i < MAX_TIMER + 1; i++) {
        fish[i] = nextGen[i];
    }
}

void simulateGrowth(long (&fish)[MAX_TIMER + 1], const int days) {
    for (int i = 0; i < days; i++) {
        iterateGeneration(fish);
    }
}

long long countFish(long (&fish)[MAX_TIMER + 1]) {
    long long count = 0;

    for (auto i = 0; i < MAX_TIMER + 1; i++) {
        count += fish[i];
    }

    return count;
}

long long answer1(std::istream& in) {
    long fish[MAX_TIMER + 1];
    initFishMap(fish);
    parseFish(fish, in);
    simulateGrowth(fish, 80);

    return countFish(fish);
}

long long answer2(std::istream& in) {
    long fish[MAX_TIMER + 1];
    initFishMap(fish);
    parseFish(fish, in);
    simulateGrowth(fish, 256);

    return countFish(fish);
}
