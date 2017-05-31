#include <iostream>
#include <vector>
#include <set>
#include <exception>
#include <limits>

typedef int vertex_t;
typedef int weight_t;

const int INF = std::numeric_limits<int>::max();
const int _INF = std::numeric_limits<int>::min();

class Graph {
	std::vector < std::vector < std::pair<vertex_t, weight_t>> > listOfAdj;
public:
	Graph(int numberOVertices = 0) : listOfAdj(numberOVertices, std::vector<std::pair<vertex_t, weight_t>>()) {}
	size_t getNumberOfVertices()const {
		return listOfAdj.size();
	}
 	void addAdjective(vertex_t begin, vertex_t end, weight_t weightOfEdge) {
		/*if (end >= getNumberOfVertices() || end < 0)
			throw std::out_of_range("Impossible to add adjective. Wrong number of vertice");*/
		listOfAdj.at(begin).push_back(std::make_pair(end, weightOfEdge));
	}
	const std::vector<std::pair<vertex_t, weight_t>> & operator[](vertex_t v)const {
		return listOfAdj.at(v);
	}
	Graph findReversedGraph()const {
		Graph reversedGraph(getNumberOfVertices());
		for (size_t i = 0; i < getNumberOfVertices(); ++i)
			for (std::vector<std::pair<vertex_t, weight_t>>::const_iterator it = listOfAdj[i].begin(); it != listOfAdj[i].end(); ++it) {
				reversedGraph.addAdjective(it->first, i, it->second);
			}
		return reversedGraph;
	}
};

struct Edge {
	vertex_t begin;
	vertex_t end;
	weight_t weight;
	Edge(vertex_t begin, vertex_t end, weight_t weight) : begin(begin), end(end), weight(weight) {}
};

bool relax(const Edge & edge, std::vector<weight_t> & distances, std::vector<vertex_t> & parents) {
	if (distances[edge.begin] != INF && (distances[edge.begin] + edge.weight < distances[edge.end])) {
		distances[edge.end] = distances[edge.begin] + edge.weight;
		parents[edge.end] = edge.begin;
		return true;
	}
	return false;
}

void DFS_visit(vertex_t vertex, std::vector<bool> & visited, const Graph & reversedGraph) {
	for (std::vector<std::pair<vertex_t, weight_t>>::const_iterator it = reversedGraph[vertex].begin();
		it != reversedGraph[vertex].end(); ++it) {
		if (!visited[it->first]) {
			visited[it->first] = true;
			DFS_visit(it->first, visited, reversedGraph);
		}
	}
}

std::vector<bool> findIsLastVertexAchievable(const Graph & graph) {
	Graph reversedGraph = graph.findReversedGraph();
	std::vector<bool> visited(graph.getNumberOfVertices(), false);
	visited[reversedGraph.getNumberOfVertices() - 1] = true;
	DFS_visit(reversedGraph.getNumberOfVertices() - 1, visited, reversedGraph);
	return visited;
}

int findDistanceToLastVertex(const Graph & graph) {
	std::vector<weight_t> distances(graph.getNumberOfVertices(), INF);
	std::vector<vertex_t> parents(graph.getNumberOfVertices(), -1);
	distances[0] = 0;
	parents[0] = 0;
	bool has_relaxed = true;
	for (size_t i = 0; i < graph.getNumberOfVertices() - 1; ++i) {
		has_relaxed = false;
		for (size_t j = 0; j < graph.getNumberOfVertices(); ++j)
			for (std::vector<std::pair<vertex_t, weight_t>>::const_iterator it = graph[j].begin(); it != graph[j].end(); ++it)
				has_relaxed = relax(Edge(j, it->first, it->second), distances, parents) || has_relaxed;
		if (!has_relaxed)
			break;
	}
	if (!has_relaxed)
		return distances[graph.getNumberOfVertices() - 1];
	std::vector<bool> lastVertexIsAchievable = findIsLastVertexAchievable(graph);
	std::vector<bool> achievableFromCycleOfNegativeWeight(graph.getNumberOfVertices(), false);
	for (size_t j = 0; j < graph.getNumberOfVertices(); ++j)
		for (std::vector<std::pair<vertex_t, weight_t>>::const_iterator it = graph[j].begin(); it != graph[j].end(); ++it) {
			if (distances[graph.getNumberOfVertices() - 1] == _INF)
				break;
			if (relax(Edge(j, it->first, it->second), distances, parents)) {
				vertex_t vertex = it->first;
				//vertex_t previousVertex = parents[vertex];
				do {
					achievableFromCycleOfNegativeWeight[vertex] = true;
					if (lastVertexIsAchievable[vertex]) {
						distances[graph.getNumberOfVertices() - 1] = _INF;
						break;
					}
					vertex = parents[vertex];
				} while (!achievableFromCycleOfNegativeWeight[vertex]);
			}
		}
	return distances[graph.getNumberOfVertices() - 1];
}

int main() {
	int n, m;
	std::cin >> n >> m;
	Graph graph(n);
	vertex_t begin, end;
	weight_t weight;
	for (int i = 0; i < m; ++i) {
		std::cin >> begin >> end >> weight;
		graph.addAdjective(begin - 1, end - 1, -weight);
	}
	weight_t distanceToLastVertex = findDistanceToLastVertex(graph);
	if (distanceToLastVertex == INF)
		std::cout << ":(" << std::endl;
	else if (distanceToLastVertex == _INF)
		std::cout << ":)" << std::endl;
	else
			std::cout << -distanceToLastVertex << std::endl;
	return 0;
}
