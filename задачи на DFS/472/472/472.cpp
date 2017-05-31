#include <iostream>
#include <vector>
#include <exception>

class Graph {
	std::vector<std::vector<int> > matrixOfAdj;
	//bool isOriented;
public:
	//Graph(size_t numberOfVertices = 0, bool isOriented = false) : matrixOfAdj(numberOfVertices, std::vector<int>(numberOfVertices)), isOriented(isOriented) {}
	Graph(size_t numberOfVertices = 0) : matrixOfAdj(numberOfVertices, std::vector<int>(numberOfVertices)) {}
	size_t getNumberOfVertices()const {
		return matrixOfAdj.size();
	}
	int getInDegree(size_t numberOfVertice)const;
	int getOutDegree(size_t numberOfVertice)const;
	friend std::istream & operator>>(std::istream & is, Graph & g);
};

int Graph::getInDegree(size_t numberOfVertice)const {
	int inDegree = 0;
	for (std::vector<std::vector<int> >::const_iterator it = matrixOfAdj.begin(); it != matrixOfAdj.end(); ++it) {
		inDegree += (*it).at(numberOfVertice);
	}
	return inDegree;
}

int Graph::getOutDegree(size_t numberOfVertice)const {
	int outDegree = 0;
	/*if (numberOfVertice > matrixOfAdj.size() - 1)
		throw std::out_of_range("Impossible to find outdegree. Wrong index");*/
	std::vector<std::vector<int> >::const_iterator it = matrixOfAdj.begin() + numberOfVertice;
	for (std::vector<int>::const_iterator it1 = (*it).begin(); it1 != (*it).end(); ++it1)
		outDegree += (*it1);
	return outDegree;
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