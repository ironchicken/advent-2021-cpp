#include <sstream>
#include <algorithm>
#include <istream>
#include <iterator>
#include <string>
#include <vector>
#include <sstream>

enum struct Direction { Forward, Down, Up };

std::ostream& operator<<(std::ostream& out, Direction d) {
    switch (d) {
    case Direction::Forward:
	out << "forward";
	break;
    case Direction::Down:
	out << "down";
	break;
    case Direction::Up:
	out << "up";
	break;
    }

    return out;
}

struct Command {
    Direction direction;
    int magnitude;
};

bool operator==(const Command &a, const Command &b) {
    return a.direction == b.direction && a.magnitude == b.magnitude;
}

struct Position {
    int horizontal;
    int depth;
};

bool operator==(const Position &a, const Position &b) {
    return a.horizontal == b.horizontal && a.depth == b.depth;
}

struct Aim {
    int aim;
    int horizontal;
    int depth;
};

bool operator==(const Aim &a, const Aim &b) {
    return a.aim == b.aim && a.horizontal == b.horizontal && a.depth == b.depth;
}

std::vector<std::string> tokenize(std::istream &in) {
    std::vector<std::string> tokens;

    std::copy(std::istream_iterator<std::string>(in),
	      std::istream_iterator<std::string>(), std::back_inserter(tokens));

    return tokens;
}

std::vector<Command> parse(std::vector<std::string> tokens) {
    std::vector<Command> commands;
    auto it = tokens.begin();
    Command next;

    while (it != tokens.end()) {
	auto token = *it;
	if (token == "forward") {
	    next.direction = Direction::Forward;
        }
        else if (token == "down") {
	    next.direction = Direction::Down;
        }
        else if (token == "up") {
	    next.direction = Direction::Up;
        } else {
	    next.magnitude = std::stoi(token);
	    commands.push_back(next);
        }
	it++;
    }

    return commands;
}

void followCommand(const Command c, Position& p) {
    switch (c.direction) {
    case Direction::Forward:
	p.horizontal += c.magnitude;
	break;
    case Direction::Down:
	p.depth += c.magnitude;
	break;
    case Direction::Up:
	p.depth -= c.magnitude;
	break;
    };
}

Position followCourse(const Position start, std::vector<Command> course) {
    Position current = start;

    for (auto command : course) {
	followCommand(command, current);
    }

    return current;
}

void followAimCommand(const Command c, Aim& p) {
    switch (c.direction) {
    case Direction::Forward:
	p.horizontal += c.magnitude;
	p.depth += p.aim * c.magnitude;
	break;
    case Direction::Down:
	p.aim += c.magnitude;
	break;
    case Direction::Up:
	p.aim -= c.magnitude;
	break;
    };
}

Aim followAimCourse(const Aim start, std::vector<Command> course) {
    Aim current = start;

    for (auto command : course) {
	followAimCommand(command, current);
    }

    return current;
}

int answer1(std::istream &in) {
    auto tokens = tokenize(in);
    auto course = parse(tokens);
    const Position start = Position{0, 0};
    auto position = followCourse(start, course);

    return position.depth * position.horizontal;
}

int answer2(std::istream &in) {
    auto tokens = tokenize(in);
    auto course = parse(tokens);
    const Aim start = Aim{0, 0, 0};
    auto position = followAimCourse(start, course);

    return position.depth * position.horizontal;
}
