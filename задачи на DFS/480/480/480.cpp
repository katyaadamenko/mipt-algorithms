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
	std::vector<int> getSources()const;
	std::vector<int> getDrains()const;
	bool isTransitive()const;
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

std::vector<int> Graph::getSources()const {
	std::vector<int> sources;
	for (size_t i = 0; i < getNumberOfVertices(); ++i)
		if (getInDegree(i) == 0)
			sources.push_back(i + 1);
	return sources;
}

std::vector<int> Graph::getDrains()const {
	std::vector<int> drains;
	for (size_t i = 0; i < getNumberOfVertices(); ++i)
		if (getOutDegree(i) == 0)
			drains.push_back(i + 1);
	return drains;
}

bool Graph::isTransitive()const {
	bool isTransitive = true;
	for (size_t i = 0; i < getNumberOfVertices() && isTransitive; ++i) {
		for (size_t j = 0; j < getNumberOfVertices() && isTransitive; ++j) {
			if (matrixOfAdj[i][j] == 1) {
				for (size_t k = 0; k < getNumberOfVertices(); ++k)
					if (matrixOfAdj[j][k] == 1 && matrixOfAdj[i][k] == 0) {
						isTransitive = false;
						break;
					}
			}
		}
	}
	return isTransitive;
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
	graph.isTransitive() ? (std::cout << "YES") : (std::cout << "NO");
	std::cout << std::endl;
	return 0;
}