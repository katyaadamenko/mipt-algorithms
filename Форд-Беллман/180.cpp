#include <iostream>
#include <vector>
#include <limits>

typedef int vertex_t;
typedef int weight_t;

const int INF = std::numeric_limits<int>::max();
const int MAX_VALUE = 100000;

struct Edge {
	vertex_t first;
	vertex_t second;
	weight_t weight;
	Edge(vertex_t first, vertex_t second, weight_t weight) : first(first), second(second), weight(weight)  {}
};

bool relax(const Edge & edge, std::vector<weight_t> & distance, std::vector<vertex_t> & parent) {
	if (distance.at(edge.first) + edge.weight < distance.at(edge.second)) {
		distance[edge.second] = distance[edge.first] + edge.weight;
		parent[edge.second] = edge.first;
		return true;
	}
	return false;
}

bool findCycleOfNegativeWeight(const std::vector<Edge> & edges, int numberOfVertices, std::vector<vertex_t> & cycleOfNegativeWeight) {
	cycleOfNegativeWeight.clear();
	std::vector<weight_t> distance(numberOfVertices, MAX_VALUE);
	distance[0] = 0;
	std::vector<vertex_t> parent(numberOfVertices, -1);
	parent[0] = 0;
	bool has_relaxed = true;
	for (int i = 0; i < numberOfVertices - 1; ++i) {
		has_relaxed = false;
		for (std::vector<Edge>::const_iterator it = edges.begin(); it != edges.end(); ++it) {
			has_relaxed = relax(*it, distance, parent) || has_relaxed;
		}
		if (!has_relaxed)
			break;
	}
	if (has_relaxed) {
		for (std::vector<Edge>::const_iterator it = edges.begin(); it != edges.end(); ++it) {
			has_relaxed = relax(*it, distance, parent);
			if (has_relaxed) {
				std::vector<bool> wasOnThePath(numberOfVertices, false);
				wasOnThePath[it->second] = true;
				vertex_t previousVertex = it->first;
				while (!wasOnThePath[previousVertex]) {
					wasOnThePath[previousVertex] = true;
					previousVertex = parent[previousVertex];
				}
				do {
					cycleOfNegativeWeight.push_back(previousVertex);
					previousVertex = parent[previousVertex];
				} while (previousVertex != cycleOfNegativeWeight[0]);
				cycleOfNegativeWeight.push_back(previousVertex);
				break;
			}
		}
	}
	return !cycleOfNegativeWeight.empty();
}

int main() {
	int n;
	std::cin >> n;
	weight_t w;
	std::vector<Edge> edges;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			std::cin >> w;
			if (w != MAX_VALUE)
				edges.push_back(Edge(i, j, w));
		}
	std::vector<vertex_t> cycleOfNegativeWeight;
	bool thereIsCycleOfNegativeWeight = findCycleOfNegativeWeight(edges, n, cycleOfNegativeWeight);
	if (thereIsCycleOfNegativeWeight) {
		std::cout << "YES" << std::endl << cycleOfNegativeWeight.size() << std::endl;
		for (std::vector<vertex_t>::reverse_iterator it = cycleOfNegativeWeight.rbegin(); it != cycleOfNegativeWeight.rend(); ++it)
			std::cout << *it + 1 << ' ';
	}
	else
		std::cout << "NO";
	char c;
	std::cin >> c;
	return 0;
}