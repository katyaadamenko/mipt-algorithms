#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <functional>

typedef int vertex_t;
typedef int weight_t;

const int INF = std::numeric_limits<int>::max();

bool findShortestPath(std::vector<vertex_t> & reversedPath, const std::vector<std::vector<weight_t>> & matrixOfAdj, vertex_t source, vertex_t final) {
	reversedPath.clear();
	std::vector<weight_t> distance(matrixOfAdj.size(), INF);
	std::vector<vertex_t> parent(matrixOfAdj.size(), -1);
	distance[source] = 0;
	parent[source] = source;
	std::priority_queue<std::pair<weight_t, vertex_t>, std::vector<std::pair<weight_t, vertex_t>>, std::greater<std::pair<weight_t, vertex_t>>> q;
	q.push(std::make_pair(distance[source], source));
	for (size_t i = 0; i < matrixOfAdj.size(); ++i) {
		vertex_t u;
		weight_t du;
		do {
			u = q.top().second;
			du = q.top().first;
			q.pop();
		} while (distance[u] != du);
		for (vertex_t v = 0; v < matrixOfAdj.size(); ++v) {
			if (distance[u] != INF && matrixOfAdj[u][v] != INF && distance[v] > distance[u] + matrixOfAdj[u][v]) {
				distance[v] = distance[u] + matrixOfAdj[u][v];
				parent[v] = u;
				q.push(std::make_pair(distance[v], v));
			}
		}
		if (u == final)
			break;
	}
	vertex_t vertex = final;
	vertex_t previousVertex = parent[final];
	while (previousVertex != vertex) {
		reversedPath.push_back(vertex);
		std::swap(vertex, previousVertex);
		previousVertex = parent[vertex];
	}
	reversedPath.push_back(vertex);
	return distance[final] != INF;
}

int main() {
	int n;
	vertex_t source, final;
	std::cin >> n >> source >> final;
	--source;
	--final;
	std::vector<std::vector<weight_t>> matrixOfAdj(n, std::vector<weight_t>(n));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			weight_t weightOfEdge;
			std::cin >> weightOfEdge;
			matrixOfAdj[i][j] = (weightOfEdge == -1 ? INF : weightOfEdge);
		}
	std::vector<vertex_t> reversedPath;
	if (!findShortestPath(reversedPath, matrixOfAdj, source, final))
		std::cout << "-1" << std::endl;
	else {
		for (std::vector<vertex_t>::reverse_iterator it = reversedPath.rbegin(); it != reversedPath.rend(); ++it)
			std::cout << *it + 1 << ' ';
		std::cout << std::endl;
	}
	return 0;
}