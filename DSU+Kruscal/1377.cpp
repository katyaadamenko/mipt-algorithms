#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>
//#include "DSU.h"

class DSU {
	std::vector<int> parentsOfElements;
	std::vector<int> ranksOfTrees;
public:
	DSU(int numberOfElements = 0) {
		parentsOfElements.reserve(numberOfElements);
		ranksOfTrees.reserve(numberOfElements);
		for (int i = 0; i < numberOfElements; ++i)
			make_set();
	}
	size_t get_number_of_elements()const {
		return parentsOfElements.size();
	}
	void make_set() {
		parentsOfElements.push_back(parentsOfElements.size());
		ranksOfTrees.push_back(0);
	}
	int find_set(size_t x) {
		/*if (x < 0 || x > get_number_of_elements())
			throw std::out_of_range("Impossible to find set: wrong element");*/
		if (parentsOfElements[x] != x)
			return parentsOfElements[x] = find_set(parentsOfElements[x]);
		return x;
	}
	void union_sets(size_t x, size_t y);
};

void DSU::union_sets(size_t x, size_t y) {
	/*if (x < 0 || x > get_number_of_elements() || y < 0 || y > get_number_of_elements())
		throw std::out_of_range("Impossible to union sets: wrong elements");*/
	x = find_set(x);
	y = find_set(y);
	if (x != y) {
		if (ranksOfTrees[x] > ranksOfTrees[y]) {
			std::swap(x, y);
		}
		parentsOfElements[x] = y;
		if (ranksOfTrees[x] == ranksOfTrees[y])
			++ranksOfTrees[y];
	}
}

typedef int vertex_t;
typedef int weight_t;

struct Edge {
	vertex_t from;
	vertex_t to;
	weight_t weight;
	Edge(vertex_t from, vertex_t to, weight_t weight) : from(from), to(to), weight(weight) {}
	bool operator <(const Edge & edge)const {
		return this->weight < edge.weight;
	}
};

weight_t findWeightOfMinSpanningTree(std::vector<Edge> & listOfEdges, int numberOfVertices) {
	weight_t weightOfMinSpanningTree = 0;
	DSU dsu(numberOfVertices);
	std::sort(listOfEdges.begin(), listOfEdges.end());
	int i = 0;
	int cnt = 0;
	vertex_t from, to;
	while (cnt < numberOfVertices - 1) {
		from = listOfEdges[i].from;
		to = listOfEdges[i].to;
		if (dsu.find_set(from) != dsu.find_set(to)) {
			weightOfMinSpanningTree += listOfEdges[i].weight;
			++cnt;
			dsu.union_sets(from, to);
		}
		++i;
	}
	return weightOfMinSpanningTree;
}


int main() {
	int n, m;
	std::cin >> n >> m;
	std::vector<Edge> listOfEdges;
	listOfEdges.reserve(m);
	vertex_t from, to;
	weight_t weight;
	for (int i = 0; i < m; ++i) {
		std::cin >> from >> to >> weight;
		listOfEdges.push_back(Edge(from - 1, to - 1, weight));
	}
	std::cout << findWeightOfMinSpanningTree(listOfEdges, n) << std::endl;
	return 0;
}