#include <iostream>
#include <vector>
#include <queue>
#include <limits>

enum color{WHITE, GRAY, BLACK};

class Graph {
	std::vector<std::vector<short> > matrixOfAdj;
public:
	Graph(size_t n = 0) : matrixOfAdj(n, std::vector<short>(n)) {}
	size_t getNumberOfVertices()const {
		return matrixOfAdj.size();
	}
	const std::vector<short> & getAdjectives(size_t vertice)const {
		return matrixOfAdj[vertice];
	}
	friend std::istream & operator >>(std::istream & is, Graph & graph);
};

std::istream & operator >>(std::istream & is, Graph & graph) {
	for (size_t i = 0; i < graph.getNumberOfVertices(); ++i)
		for (size_t j = 0; j < graph.getNumberOfVertices(); ++j)
			is >> graph.matrixOfAdj[i][j];
	return is;
}

int findShortestPath(Graph graph, size_t firstVertice, size_t lastVertice, std::deque<int> & path) {
	int length = -1;
	std::vector<color> colorsOfVertices(graph.getNumberOfVertices(), WHITE);
	std::vector<int> D(graph.getNumberOfVertices(), std::numeric_limits<int>::max());
	std::queue<int> Q;
	D[firstVertice] = 0;
	colorsOfVertices[firstVertice] = GRAY;
	Q.push(firstVertice);
	size_t v;
	std::vector<int> previousVertice(graph.getNumberOfVertices());
	while (!Q.empty()) {
		v = Q.front();
		Q.pop();
		for (size_t i = 0; i < graph.getNumberOfVertices(); ++i)
			if (graph.getAdjectives(v)[i] == 1 && colorsOfVertices[i] == WHITE) {
				colorsOfVertices[i] = GRAY;
				Q.push(i);
				D[i] = D[v] + 1;
				previousVertice[i] = v;
				if (i == lastVertice)
					break;
			}
		colorsOfVertices[v] = BLACK;
		if (colorsOfVertices[lastVertice] != WHITE) {
			length = D[lastVertice];
			break;
		}
	}
	if (length != 0 && length != -1) {
		path.clear();
		path.push_front(lastVertice);
		v = lastVertice;
		while (v != firstVertice) {
			v = previousVertice[v];
			path.push_front(v);
		}
	}
	return length;
}

int main() {
	int n;
	std::cin >> n;
	Graph graph(n);
	size_t firstVertice, lastVertice;
	std::cin >> graph >> firstVertice >> lastVertice;
	std::deque<int> path;
	int length = findShortestPath(graph, firstVertice - 1, lastVertice - 1, path);
	std::cout << length << std::endl;
	if (length != 0 && length != -1) {
		while (!path.empty()) {
			std::cout << path.front() + 1 << ' ';
			path.pop_front();
		}
	}
	return 0;
}