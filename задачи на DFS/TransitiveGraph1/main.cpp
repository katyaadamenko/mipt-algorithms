#include <iostream>
#include "Graph.h"

int main() {
	int n;
	std::cin >> n;
	Graph graph(n);
	std::cin >> graph;
	for (int i = 0; i < n; ++i) {
		std::cout << graph.getInDegree(i) << std::endl;
		std::cout << graph.getOutDegree(i) << std::endl;
	}
	return 0;
}