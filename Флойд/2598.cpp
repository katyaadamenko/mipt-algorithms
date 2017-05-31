#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <iterator>

typedef int weight_t;
typedef int vertex_t;
typedef int number_of_flight_t;

const int INF = std::numeric_limits<int>::max();

void findPath(vertex_t first, vertex_t last, std::vector<std::vector<vertex_t>> & intermediateVertex, 
	const std::vector<std::vector<std::pair<weight_t, number_of_flight_t>>> & matrixOfFlights,std::vector<vertex_t> & path) {
	vertex_t k = intermediateVertex[first][last];
	if (k == -1) {
		path.push_back(matrixOfFlights[first][last].second);
		return;
	}
	findPath(first, k, intermediateVertex, matrixOfFlights, path);
	findPath(k, last, intermediateVertex, matrixOfFlights, path);
}

bool findRoute(const std::vector<std::vector<std::pair<weight_t, number_of_flight_t>>> & matrixOfFlights, const std::vector<vertex_t> & destinations, std::vector<vertex_t> & route) {
	std::vector<std::vector<vertex_t> > matrixOfAdj(matrixOfFlights.size(), std::vector<vertex_t>(matrixOfFlights.size()));
	for (size_t i = 0; i < matrixOfFlights.size(); ++i)
		for (size_t j = 0; j < matrixOfFlights.size(); ++j)
			matrixOfAdj[i][j] = matrixOfFlights[i][j].first;
	route.clear();
	bool thereIsCycleOfNegativeWeight = false;
	std::vector<std::vector<vertex_t>> intermediateVertex(matrixOfAdj.size(), std::vector<vertex_t>(matrixOfAdj.size(), -1));
	for (size_t k = 0; k < matrixOfAdj.size(); ++k)
		for (size_t i = 0; i < matrixOfAdj.size(); ++i)
			for (size_t j = 0; j < matrixOfAdj.size(); ++j)
				if (matrixOfAdj[i][k] != INF && matrixOfAdj[k][j] != INF && matrixOfAdj[i][j] > matrixOfAdj[i][k] + matrixOfAdj[k][j]) {
					matrixOfAdj[i][j] = matrixOfAdj[i][k] + matrixOfAdj[k][j];
					if (i != k && j != k)
						intermediateVertex[i][j] = k;
				}
	std::vector<vertex_t> path;
	//std::back_insert_iterator<std::vector<vertex_t>> back_it(route);
	//route.push_back(destinations[0]);
	if (matrixOfAdj[destinations[0]][destinations[0]] < 0)
		thereIsCycleOfNegativeWeight = true;
	for (size_t i = 0; i < destinations.size() - 1 && !thereIsCycleOfNegativeWeight; ++i) {
		path.clear();
		if (matrixOfAdj[destinations[i + 1]][destinations[i + 1]] < 0) {
			thereIsCycleOfNegativeWeight = true;
			break;
		}
		findPath(destinations[i], destinations[i + 1], intermediateVertex, matrixOfFlights, path);
		std::copy(path.begin(), path.end(), std::back_inserter(route));
		//route.push_back(destinations[i + 1]);
	}
	return !thereIsCycleOfNegativeWeight;
}

int main() {
	int n, m, k;
	std::cin >> n >> m >> k;
	//std::vector<std::vector<weight_t>> matrixOfAdj(n, std::vector<weight_t>(n, INF));
	std::vector < std::vector<std::pair<weight_t, number_of_flight_t>>> matrixOfFlights(n, std::vector<std::pair<weight_t, number_of_flight_t>>(n, std::make_pair(INF, -1)));
	vertex_t first, second;
	weight_t weightOfEdge;
	//for (int i = 0; i < n; ++i)
	//	matrixOfAdj[i][i] = 0;
	for (int i = 0; i < n; ++i)
		matrixOfFlights[i][i] = std::make_pair(0, 0);
	/*for (int i = 0; i < m; ++i) {
		std::cin >> first >> second >> weightOfEdge;
		matrixOfAdj[first - 1][second - 1] = -weightOfEdge;
	}*/
	for (int i = 0; i < m; ++i) {
		std::cin >> first >> second >> weightOfEdge;
		if (first == second && weightOfEdge > 0) {
			std::cout << "infinitely kind" << std::endl;
			break;
		}
		matrixOfFlights[first - 1][second - 1] = std::make_pair(-weightOfEdge, i + 1);
	}
	std::vector<vertex_t> destinations(k);
	vertex_t destination;
	for (int i = 0; i < k; ++i) {
		std::cin >> destination;
		destinations[i] = destination - 1;
	}
	std::vector<vertex_t> route;
	if (findRoute(matrixOfFlights, destinations, route)) {
		std::cout << route.size() << std::endl;
		for (std::vector<vertex_t>::iterator it = route.begin(); it != route.end(); ++it)
			std::cout << *it << ' ';
		std::cout << std::endl;
	}
	else
		std::cout << "infinitely kind" << std::endl;
	return 0;
}