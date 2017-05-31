#include <iostream>
#include <vector>
#include <list>
#include <exception>

enum color { WHITE, GRAY, BLACK };

class Graph {
	std::vector<std::vector<int> > matrixOfAdj;
	std::vector<color> colorsOfVertices;
	bool isOriented;
protected:
	bool DFS_visit_to_sort(size_t vertex, std::list<int> & sortedVertices);
	size_t DFS_visit(size_t vertex, std::vector<int> & connectedComponent);
public:
	Graph(size_t numberOfVertices = 0, bool isOriented = false) : matrixOfAdj(numberOfVertices, std::vector<int>(numberOfVertices, 0)),
		colorsOfVertices(numberOfVertices, WHITE), isOriented(isOriented){}
	size_t getNumberOfVertices()const {
		return matrixOfAdj.size();
	}
	size_t getNumberOfEdges()const;
	void addEdge(size_t beggining, size_t end);
	std::vector<std::vector<int> > DFS();
	std::list<int> TopSort();
	friend std::istream & operator>>(std::istream & is, Graph & g);
};

void Graph::addEdge(size_t beggining, size_t end) {
	if (!matrixOfAdj[beggining][end])
		matrixOfAdj[beggining][end] = 1;
	if (!isOriented)
		matrixOfAdj[end][beggining] = 1;
}

size_t Graph::getNumberOfEdges()const {
	size_t numberOfEdges = 0;
	for (size_t i = 0; i < getNumberOfVertices(); ++i)
		for (size_t j = i + 1; j < getNumberOfVertices(); ++j)
			numberOfEdges += matrixOfAdj[i][j];
	return numberOfEdges;
}

std::istream & operator>>(std::istream & is, Graph & g) {
	int newElement;
	for (std::vector<std::vector<int> >::iterator it = g.matrixOfAdj.begin(); it != g.matrixOfAdj.end(); ++it)
		for (std::vector<int>::iterator it1 = (*it).begin(); it1 != (*it).end(); ++it1) {
			is >> newElement;
			/*if (newElement != 0 && newElement != 1)
			throw std::out_of_range("Impossible element in matrix of adjectives");*/
			*it1 = newElement;
		}
	return is;
}

size_t Graph::DFS_visit(size_t vertex, std::vector<int> & connectedComponent) {
	static int numberOfVerticesInTree = 1;
	connectedComponent.push_back(vertex);
	colorsOfVertices[vertex] = GRAY;
	std::vector<std::vector<int>>::iterator it1 = matrixOfAdj.begin() + vertex;
	for (size_t i = 0; i < getNumberOfVertices(); ++i) {
		if (matrixOfAdj[vertex][i] == 1 && colorsOfVertices[i] == WHITE) {
			++numberOfVerticesInTree;
			DFS_visit(i, connectedComponent);
		}
	}
	colorsOfVertices[vertex] = BLACK;
	return numberOfVerticesInTree;
}

std::vector<std::vector<int>> Graph::DFS() {
	std::vector<std::vector<int>> forest;
	for (std::vector<color> ::iterator it = colorsOfVertices.begin(); it != colorsOfVertices.end(); ++it)
		*it = WHITE;
	for (size_t i = 0; i < getNumberOfVertices(); ++i) {
		if (colorsOfVertices[i] == WHITE) {
			forest.push_back(std::vector<int>());
			DFS_visit(i, *(forest.end() - 1));
		}
	}
	return forest;
}

bool Graph::DFS_visit_to_sort(size_t vertex, std::list<int> & sortedVertices) {
	colorsOfVertices[vertex] = GRAY;
	bool isPossibleToSort = true;
	std::vector<std::vector<int>>::iterator it1 = matrixOfAdj.begin() + vertex;
	for (std::vector<int>::iterator it = it1->begin();
		it != it1->end(); ++it) {
		size_t verifiableVertex = it - it1->begin();
		if (*it == 1 && colorsOfVertices[verifiableVertex] == WHITE) {
			isPossibleToSort = DFS_visit_to_sort(verifiableVertex, sortedVertices);
		}
		else if (*it == 1 && colorsOfVertices[verifiableVertex] == GRAY)
			isPossibleToSort = false;
		if (!isPossibleToSort)
			break;
	}
	colorsOfVertices[vertex] = BLACK;
	sortedVertices.push_front(vertex);
	return isPossibleToSort;
}

std::list<int> Graph::TopSort() {
	std::list<int> sortedVertices;
	if (isOriented) {
		bool isPossibleToSort = true;
		for (std::vector<color> ::iterator it = colorsOfVertices.begin(); it != colorsOfVertices.end(); ++it)
			*it = WHITE;
		for (size_t i = 0; i < getNumberOfVertices(); ++i) {
			if (colorsOfVertices[i] == WHITE) {
				isPossibleToSort = DFS_visit_to_sort(i, sortedVertices);
			}
			if (!isPossibleToSort)
				break;
		}
		if (!isPossibleToSort)
			sortedVertices.clear();
	}
	return sortedVertices;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	Graph graph(n, true);
	size_t beggining, end;
	for (int i = 0; i < m; ++i) {
		std::cin >> beggining >> end;
		graph.addEdge(beggining - 1, end - 1);
	}
	std::list<int> sortedVertices = graph.TopSort();
	if (sortedVertices.empty())
		std::cout << "No" << std::endl;
	else {
		std::cout << "Yes" << std::endl;
		for (std::list<int>::iterator it = sortedVertices.begin(); it != sortedVertices.end(); ++it)
			std::cout << *it + 1 << ' ';
		std::cout << std::endl;
	}
	return 0;
}