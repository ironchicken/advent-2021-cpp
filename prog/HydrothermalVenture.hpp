#include <istream>
#include <sstream>
#include <string>
#include <vector>

struct Point {
    int x;
    int y;
};

bool operator==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

struct LineSegment {
    Point from;
    Point to;
};

bool operator==(const LineSegment &a, const LineSegment &b) {
    return a.from == b.from && a.to == b.to;
}

std::vector<LineSegment> parseLineSegments(std::istream& in, int& width, int& height) {
    std::vector<LineSegment> lineSegments;

    std::string line;
    while (std::getline(in, line)) {
	int sPos = 0;
	int ePos = line.find(',');
	auto x1 = std::stoi(line.substr(sPos, ePos));
        if (x1 > width) {
	    width = x1;
        }

        sPos = ePos + 1;
        ePos = line.find(' ', sPos);
        auto y1 = std::stoi(line.substr(sPos, ePos));
        if (y1 > height) {
	    height = y1;
	}

        sPos = ePos + 4;
	ePos = line.find(',', sPos);
	auto x2 = std::stoi(line.substr(sPos, ePos));
        if (x2 > width) {
	    width = x2;
        }

	sPos = ePos + 1;
	auto y2 = std::stoi(line.substr(sPos));
        if (y2 > height) {
	    height = y2;
	}

        lineSegments.emplace_back(LineSegment{Point{x1, y1}, Point{x2, y2}});
    }

    return lineSegments;
}

using Map = std::vector<std::vector<int>>;

bool isHorizontal(const LineSegment &line) { return line.from.y == line.to.y; }
bool isVertical(const LineSegment &line) { return line.from.x == line.to.x; }
bool isForwards(const LineSegment &line) { return line.from.x < line.to.x; }
bool isBackwards(const LineSegment &line) { return line.from.x > line.to.x; }
bool isUpwards(const LineSegment &line) { return line.from.y > line.to.y; }
bool isDownwards(const LineSegment &line) { return line.from.y < line.to.y; }

std::vector<Point> findPoints(const LineSegment &line) {
    std::vector<Point> points;

    if (isHorizontal(line)) {
	if (isForwards(line)) {
	    for (int x { line.from.x }; x <= line.to.x; x++ ) {
		points.emplace_back(Point{ x, line.from.y });
            }
        } else if (isBackwards(line)) {
	    for (int x { line.from.x }; x >= line.to.x; x-- ) {
		points.emplace_back(Point{ x, line.from.y });
            }
        }
    } else if (isVertical(line)) {
	if (isUpwards(line)) {
	    for (int y { line.from.y }; y >= line.to.y; y-- ) {
		points.emplace_back(Point{ line.from.x, y });
            }
        } else if (isDownwards(line)) {
	    for (int y { line.from.y }; y <= line.to.y; y++ ) {
		points.emplace_back(Point{ line.from.x, y });
            }
        }
    }

    return points;
}

void addLinesToMap(const std::vector<LineSegment>& lines, Map& map, int width, int height) {
    for (int y { 0 }; y <= height; y++) {
	map.push_back(std::vector(width + 1, 0));
    }

    for (auto line : lines) {
	auto points = findPoints(line);
        for (auto p : points) {
            map[p.y][p.x]++;
        }
    }
}

int countOverlaps(const Map& map) {
    int count { 0 };

    for (auto row : map) {
	for (auto col : row) {
	    if (col > 1) {
		count++;
	    }
        }
    }

    return count;
}

int answer1(std::istream& in) {
    int width { 0 };
    int height { 0 };
    Map map;

    auto lines = parseLineSegments(in, width, height);

    addLinesToMap(lines, map, width, height);

    return countOverlaps(map);
}
