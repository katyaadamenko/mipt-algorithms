#include <iostream>
#include <vector>
#include <exception>

typedef int time_type;
enum color { WHITE, GRAY, BLACK };

class Graph {
	std::vector<std::vector<int> > matrixOfAdj;
	std::vector<color> colorsOfVertices;
	//bool DFS_visit_isGraphTree(size_t vertex);
protected:
	size_t DFS_visit(size_t vertex, std::vector<int> & connectedComponent);
public:
	Graph(size_t numberOfVertices = 0) : matrixOfAdj(numberOfVertices, std::vector<int>(numberOfVertices)), colorsOfVertices(numberOfVertices, WHITE){}
	size_t getNumberOfVertices()const {
		return matrixOfAdj.size();
	}
	size_t getNumberOfEdges()const;
	bool isTree();
	std::vector<std::vector<int> > DFS();
	friend std::istream & operator>>(std::istream & is, Graph & g);
};

//time_type Graph::time = 0;

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

/*bool Graph::DFS_visit_isGraphTree(size_t vertex) {
	bool isTree = true;
	colorsOfVertices[vertex] = GRAY;
	for (size_t i = 0; i < getNumberOfVertices(); ++i) {
		if (matrixOfAdj[vertex][i] == 1 && colorsOfVertices[i] == WHITE)
			isTree = DFS_visit_isGraphTree(i);
		else if (matrixOfAdj[vertex][i] == 1)
			isTree = false;
		if (!isTree)
			break;
	}
	colorsOfVertices[vertex] = BLACK;
	return isTree;
}*/


bool Graph::isTree() {
	std::vector<std::vector<int>> forest = DFS();
	/*for (std::vector<color> ::iterator it = colorsOfVertices.begin(); it != colorsOfVertices.end(); ++it)
		*it = WHITE;
	isTree = DFS_visit_isGraphTree(0);
	if (isTree) {
		for (size_t i = 1; i < getNumberOfVertices(); ++i)
			if (colorsOfVertices[i] != BLACK) {
				isTree = false;
				break;
			}
	}*/
	return (getNumberOfEdges() == getNumberOfVertices() - 1) && forest.size() == 1;
}

int main() {
	int n;
	std::cin >> n;
	Graph graph(n);
	std::cin >> graph;
	graph.isTree() ? std::cout << "YES" : std::cout << "NO";
	std::cout << std::endl;
	return 0;
}