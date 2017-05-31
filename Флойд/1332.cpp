#include <iostream>
#include <vector>

std::vector<std::vector<bool>> findTransitiveClosure(std::vector<std::vector<bool>> matrixOfAdj) {
	for (size_t k = 0; k < matrixOfAdj.size(); ++k)
		for (size_t i = 0; i < matrixOfAdj.size(); ++i)
			for (size_t j = 0; j < matrixOfAdj.size(); ++j)
				matrixOfAdj[i][j] = matrixOfAdj[i][j] || matrixOfAdj[i][k] && matrixOfAdj[k][j];
	return matrixOfAdj;
}

int main() {
	int numberOfVertices;
	std::cin >> numberOfVertices;
	std::vector<std::vector<bool>> matrixOfAdj(numberOfVertices, std::vector<bool>(numberOfVertices));
	bool thereIsEdge;
	for (int i = 0; i < numberOfVertices; ++i)
		for (int j = 0; j < numberOfVertices; ++j) {
			std::cin >> thereIsEdge;
			matrixOfAdj[i][j] = thereIsEdge;
		}
	std::vector<std::vector<bool>> transitiveClosure = findTransitiveClosure(matrixOfAdj);
	for (int i = 0; i < numberOfVertices; ++i) {
		for (int j = 0; j < numberOfVertices; ++j)
			std::cout << transitiveClosure[i][j] << ' ';
		std::cout << std::endl;
	}
	return 0;
}