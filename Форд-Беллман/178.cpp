#include <iostream>
#include <vector>
#include <limits>

typedef int vertex_t;
typedef int weight_t;

const int INF = std::numeric_limits<int>::max();

struct Edge {
	vertex_t first;
	vertex_t last;
	weight_t weight;
	Edge(vertex_t first, vertex_t last, weight_t weight) : first(first), last(last), weight(weight){}
};

bool relax(const Edge & edge, std::vector<weight_t> & distance) {
	if (distance[edge.first] != INF && (distance[edge.first] + edge.weight < distance[edge.last])) {
		distance[edge.last] = distance[edge.first] + edge.weight;
		return true;
	}
	return false;
}

std::vector<weight_t> findLengthOfShortestPaths(const std::vector<Edge> & edges, int numberOfVertices) {
	bool has_relaxed;
	std::vector<weight_t> distance(numberOfVertices, INF);
	distance[0] = 0;
	for (int i = 0; i < numberOfVertices - 1; ++i) {
		has_relaxed = false;
		for (std::vector<Edge>::const_iterator it = edges.begin(); it != edges.end(); ++it)
			has_relaxed = relax(*it, distance) || has_relaxed;
		if (!has_relaxed)
			break;
	}
	return distance;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	std::vector<Edge> edges;
	edges.reserve(m);
	vertex_t first, last;
	weight_t weight;
	for (int i = 0; i < m; ++i) {
		std::cin >> first >> last >> weight;
		edges.push_back(Edge(first - 1, last - 1, weight));
	}
	std::vector<weight_t> lengthOfShortestPaths = findLengthOfShortestPaths(edges, n);
	for (std::vector<weight_t>::iterator it = lengthOfShortestPaths.begin(); it != lengthOfShortestPaths.end(); ++it) {
		if (*it != INF)
			std::cout << *it << ' ';
		else
			std::cout << "30000" << ' ';
	}
	return 0;
}