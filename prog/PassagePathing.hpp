#include <cctype>
#include <iterator>
#include <istream>
#include <string>
#include <utility>
#include <vector>

enum struct NodeType {Start, End, Large, Small};

std::ostream& operator<<(std::ostream& out, NodeType nt) {
    switch (nt) {
    case NodeType::Start:
	out << "start";
	break;
    case NodeType::End:
	out << "end";
	break;
    case NodeType::Large:
	out << "large";
	break;
    case NodeType::Small:
	out << "small";
	break;
    }

    return out;
}

struct Node {
    NodeType type;
    std::string name;
};

bool operator==(const Node &a, const Node &b) {
    return a.type == b.type && a.name == b.name;
}

std::ostream& operator<<(std::ostream& out, Node n) {
    out << "{" << n.type << ", " << n.name << "}";
    return out;
}

bool isUpper(const std::string &s) {
    for (auto c : s) {
	if (!std::isupper(c)) {
	    return false;
	}
    }
    return true;
  }

Node parseToken(const std::string& t) {
    if (t == "start") {
	return Node { NodeType::Start, "" };
    } else if (t == "end") {
	return Node { NodeType::End, "" };
    } else if (isUpper(t)) {
	return Node { NodeType::Large, t };
    } else {
	return Node { NodeType::Small, t };
    }

    throw "Failed to parse";
}

std::vector<std::string> tokenize(std::istream& in) {
    std::vector<std::string> tokens;

    std::copy(std::istream_iterator<std::string>(in),
	      std::istream_iterator<std::string>(),
	      std::back_inserter(tokens));

    return tokens;
}

using Map = std::vector<std::pair<Node, Node>>;

Map parseMap(std::vector<std::string> tokens) {
    Map nodes;

    for (auto t : tokens) {
	auto delim = t.find("-");
	auto from = t.substr(0, delim);
	auto to = t.substr(delim + 1);

	nodes.push_back(std::make_pair(parseToken(from), parseToken(to)));
    }

    return nodes;
}

long answer1(std::istream &in) {
    auto tokens = tokenize(in);

    return 0;
}
