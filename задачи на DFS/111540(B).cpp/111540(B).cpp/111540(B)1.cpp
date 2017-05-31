#include <iostream>
#include <vector>
#include <exception>

typedef int time_type;
enum color { WHITE, GRAY, BLACK };

class Graph {
	std::vector<std::vector<int> > listOfAdj;
	std::vector<color> colorsOfVertices;
	std::vector<time_type> D;
	std::vector<time_type> F;
	static time_type time;
protected:
	size_t DFS_visit(size_t vertex, std::vector<int> & connectedComponent);
public:
	Graph(size_t numberOfVertices = 0) : listOfAdj(numberOfVertices, std::vector<int>()), colorsOfVertices(numberOfVertices, WHITE),
		D(numberOfVertices), F(numberOfVertices){}
	size_t getNumberOfVertices()const {
		return listOfAdj.size();
	}
	void addEdge(size_t i, size_t j) {
		//if (i == j || i >= getNumberOfVertices() || j >= getNumberOfVertices())
		//	throw std::out_of_range("Impossible to add edge. Wrong vertices");
		listOfAdj[i].push_back(j);
		listOfAdj[j].push_back(i);
	}
	std::vector<std::vector<int> > DFS();
};

time_type Graph::time = 0;

size_t Graph::DFS_visit(size_t vertex, std::vector<int> & connectedComponent) {
	static int numberOfVerticesInTree = 1;
	connectedComponent.push_back(vertex);
	colorsOfVertices[vertex] = GRAY;
	++time;
	D[vertex] = time;
	std::vector<std::vector<int>>::iterator it1 = listOfAdj.begin() + vertex;
	for (std::vector<int>::iterator it = it1->begin();
		it != it1->end(); ++it) {
		if (colorsOfVertices[*it] == WHITE) {
			++numberOfVerticesInTree;
			DFS_visit(*it, connectedComponent);
		}
	}
	colorsOfVertices[vertex] = BLACK;
	++time;
	F[vertex] = time;
	return numberOfVerticesInTree;
}

std::vector<std::vector<int>> Graph::DFS() {
	std::vector<std::vector<int>> forest;
	for (std::vector<color> ::iterator it = colorsOfVertices.begin(); it != colorsOfVertices.end(); ++it)
		*it = WHITE;
	time = 0;
	for (size_t i = 0; i < getNumberOfVertices(); ++i) {
		if (colorsOfVertices[i] == WHITE) {
			forest.push_back(std::vector<int>());
			DFS_visit(i, *(forest.end() - 1));
		}
	}
	return forest;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	Graph graph(n);
	size_t firstVertex, secondVertex;
	for (int i = 0; i < m; ++i) {
		std::cin >> firstVertex >> secondVertex;
		graph.addEdge(firstVertex - 1, secondVertex - 1);
	}
	std::vector<std::vector<int>> forest = graph.DFS();
	std::cout << forest.size() << std::endl;
	for (std::vector<std::vector<int>>::iterator it = forest.begin(); it != forest.end(); ++it) {
		std::cout << it->size() << std::endl;
		for (std::vector<int> ::iterator it1 = it->begin(); it1 != it->end(); ++it1)
			std::cout << *it1 + 1 << ' ';
		std::cout << std::endl;
	}
	return 0;
}