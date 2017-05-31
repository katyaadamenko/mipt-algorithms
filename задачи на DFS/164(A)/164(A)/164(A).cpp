#include <iostream>
#include <vector>
#include <exception>

typedef int time_type;
enum color { WHITE, GRAY, BLACK };

class Graph {
	std::vector<std::vector<int> > matrixOfAdj;
	std::vector<color> colorsOfVertices;
	std::vector<time_type> D;
	std::vector<time_type> F;
	static time_type time;
public:
	Graph(size_t numberOfVertices = 0) : matrixOfAdj(numberOfVertices, std::vector<int>(numberOfVertices)), colorsOfVertices(numberOfVertices, WHITE),
	D(numberOfVertices), F(numberOfVertices){}
	size_t getNumberOfVertices()const {
		return matrixOfAdj.size();
	}
	int getInDegree(size_t vertex)const;
	int getOutDegree(size_t vertex)const;
	std::vector<int> getSources()const;
	std::vector<int> getDrains()const;
	bool isTransitive()const;
	size_t DFS_visit(size_t vertex);
	friend std::istream & operator>>(std::istream & is, Graph & g);
};

time_type Graph::time = 0;

int Graph::getInDegree(size_t vertex)const {
	int inDegree = 0;
	for (std::vector<std::vector<int> >::const_iterator it = matrixOfAdj.begin(); it != matrixOfAdj.end(); ++it) {
		inDegree += (*it).at(vertex);
	}
	return inDegree;
}

int Graph::getOutDegree(size_t vertex)const {
	int outDegree = 0;
	/*if (numberOfVertice > matrixOfAdj.size() - 1)
	throw std::out_of_range("Impossible to find outdegree. Wrong index");*/
	std::vector<std::vector<int> >::const_iterator it = matrixOfAdj.begin() + vertex;
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

size_t Graph:: DFS_visit(size_t vertex) {
	static int numberOfVerticesInTree = 1;
	colorsOfVertices[vertex] = GRAY;
	++time;
	D[vertex] = time;
	std::vector<std::vector<int>>::iterator it1 = matrixOfAdj.begin() + vertex;
	for (std::vector<int>::iterator it = it1->begin();
		it != it1->end(); ++it) {
		size_t verifiableVertex = it - it1->begin();
		if (*it == 1 && colorsOfVertices[verifiableVertex] == WHITE) {
			++numberOfVerticesInTree;
			DFS_visit(verifiableVertex);
		}
	}
	colorsOfVertices[vertex] = BLACK;
	++time;
	F[vertex] = time;
	return numberOfVerticesInTree;
}

int main() {
	int n, s;
	std::cin >> n >> s;
	Graph graph(n);
	std::cin >> graph;
	std::cout << graph.DFS_visit(s - 1) << std::endl;
	return 0;
}