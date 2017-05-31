#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

typedef int vertex_t;
typedef int weight_t;

const int INF = std::numeric_limits<int>::max();

weight_t findLengthOfShortestPath(std::vector < std::vector<weight_t> > matrixOfAdj, vertex_t source, vertex_t final) {
	for (size_t k = 0; k < matrixOfAdj.size(); ++k)
		for (size_t i = 0; i < matrixOfAdj.size(); ++i)
			for (size_t j = 0; j < matrixOfAdj.size(); ++j)
				if (i != j && matrixOfAdj[i][k] != INF && matrixOfAdj[k][j] != INF)
				matrixOfAdj[i][j] = std::min(matrixOfAdj[i][j], matrixOfAdj[i][k] + matrixOfAdj[k][j]);
	return matrixOfAdj[source][final];
}

int main() {
	int numberOfVertices;
	vertex_t source, final;
	std::cin >> numberOfVertices >> source >> final;
	weight_t weightOfEdge;
	std::vector<std::vector<weight_t>> matrixOfAdj(numberOfVertices, std::vector<weight_t>(numberOfVertices));
	for (size_t i = 0; i < matrixOfAdj.size(); ++i)
		for (size_t j = 0; j < matrixOfAdj.size(); ++j) {
			std::cin >> weightOfEdge;
			matrixOfAdj[i][j] = (weightOfEdge == -1 ? INF : weightOfEdge);
		}
	weight_t lengthOfShortestPath = findLengthOfShortestPath(matrixOfAdj, source - 1, final - 1);
	std::cout << (lengthOfShortestPath == INF ? -1 : lengthOfShortestPath) << std::endl;
	return 0;
}