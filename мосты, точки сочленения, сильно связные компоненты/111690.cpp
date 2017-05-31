#include <iostream>
#include <vector>
#include <algorithm>

typedef int vertex_t;
typedef int time_type;

class Graph {
	std::vector<std::vector<vertex_t>> listOfAdj;
public:
	Graph(int numberOfVertices) :listOfAdj(numberOfVertices, std::vector<vertex_t>()) {}
	int getNumberOfVertices()const {
		return listOfAdj.size();
	}
	void addEdge(vertex_t first, vertex_t second) {
		if (first < 0 || second < 0 || first > getNumberOfVertices() || second > getNumberOfVertices())
			throw std::out_of_range("Wrong numbers of vertices");
		listOfAdj[first].push_back(second);
		listOfAdj[second].push_back(first);
	}
	const std::vector<vertex_t> & getAdjectives(vertex_t vertex)const {
		return listOfAdj[vertex];
	}
};

struct GraphData {
	std::vector<bool> visited;
	std::vector<int> up;
	std::vector<time_type> tin;
	std::vector<vertex_t> articulationPoints;
	//std::set<vertex_t> articulationPoints;
	GraphData(const Graph & graph) : visited(graph.getNumberOfVertices(), false), up(graph.getNumberOfVertices(), -1), tin(graph.getNumberOfVertices(), -1){}
};

void DFS_visit_to_find_articulation_points(vertex_t vertex, vertex_t parent, const Graph & graph, GraphData & graphData) {
	static time_type time = 1;
	graphData.visited[vertex] = true;
	graphData.up[vertex] = graphData.tin[vertex] = time++;
	bool isArticulationPoint = false;
	bool isRoot = (vertex == parent);
	int numberOfChildren = 0;
	for (size_t i = 0; i < graph.getAdjectives(vertex).size(); ++i) {
		vertex_t adjective = graph.getAdjectives(vertex)[i];
		if (adjective == parent)
			continue;
		else if (graphData.visited[adjective])
			graphData.up[vertex] = std::min(graphData.up[vertex], graphData.tin[adjective]);
		else {
			++numberOfChildren;
			DFS_visit_to_find_articulation_points(adjective, vertex, graph, graphData);
			graphData.up[vertex] = std::min(graphData.up[vertex], graphData.up[adjective]);
			if (((!isRoot && (graphData.up[adjective] >= graphData.tin[vertex])) || (isRoot && numberOfChildren > 1)) && !isArticulationPoint) {
				isArticulationPoint = true; 
				graphData.articulationPoints.push_back(vertex);
				//graphData.articulationPoints.insert(vertex);
			}
		}
	}
}

std::vector<vertex_t> findArticulationPoints(const Graph & graph) {
	GraphData graphData(graph);
	for (int i = 0; i < graph.getNumberOfVertices(); ++i)
		if (!graphData.visited[i])
			DFS_visit_to_find_articulation_points(i, i, graph, graphData);
	return graphData.articulationPoints;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	Graph graph(n);
	vertex_t first, second;
	for (int i = 0; i < m; ++i) {
		std::cin >> first >> second;
		try {
			graph.addEdge(first - 1, second - 1);
		}
		catch (std::out_of_range & ex) {
			std::cerr << ex.what() << std::endl;
		}
	}
	std::vector<vertex_t> articulationPoints = findArticulationPoints(graph);
	std::sort(articulationPoints.begin(), articulationPoints.end());
	std::cout << articulationPoints.size() << std::endl;
	for (size_t i = 0; i < articulationPoints.size(); ++i)
		std::cout << articulationPoints[i] + 1 << std::endl;
	/*for (std::set<vertex_t>::iterator it = articulationPoints.begin(); it != articulationPoints.end(); ++it)
		std::cout << *it + 1 << std::endl;*/
	return 0;
}