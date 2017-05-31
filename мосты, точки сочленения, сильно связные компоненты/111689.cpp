#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>

typedef int adjective_t;
typedef int number_of_edge_t;
typedef int time_type;

struct GraphData {
	std::vector<std::vector<std::pair<adjective_t, number_of_edge_t> > > listOfAdj;
	std::vector<bool> visited;
	std::vector<time_type> tin;
	std::vector<int> up;
	std::vector<number_of_edge_t> bridges;
	GraphData(int numberOfVertices) : listOfAdj(numberOfVertices, std::vector<std::pair<adjective_t, number_of_edge_t> >()),
		visited(numberOfVertices, false), tin(numberOfVertices, -1), bridges(0), up(numberOfVertices, -1){}
	void addEdge(size_t firstVertex, size_t secondVertex) {
		static number_of_edge_t i = 1;
		if (firstVertex < 0 || secondVertex < 0 || firstVertex >(getNumberOfVertices() - 1) || secondVertex >(getNumberOfVertices() - 1))
			throw std::out_of_range("Impossible to add edge. Wrong numbers of vertices");
		listOfAdj[firstVertex].push_back(std::make_pair(secondVertex, i));
		listOfAdj[secondVertex].push_back(std::make_pair(firstVertex, i));
		++i;
	}
	size_t getNumberOfVertices()const {
		return listOfAdj.size();
	}
};

void DFS_visit(size_t vertex, size_t parent, GraphData & graphData) {
	static time_type time = 0;
	graphData.tin[vertex] = time++;
	graphData.visited[vertex] = true;
	graphData.up[vertex] = graphData.tin[vertex];
	int numberOfEdgesToParent = 0;
	for (size_t i = 0; i < graphData.listOfAdj[vertex].size(); ++i) {
		adjective_t adjective = graphData.listOfAdj[vertex][i].first;
		if (adjective == parent) {
			if (numberOfEdgesToParent) {
				graphData.up[vertex] = std::min(graphData.up[vertex], graphData.tin[adjective]);
			}
			++numberOfEdgesToParent;
			continue;
		}
		else if (graphData.visited[adjective]) {
			graphData.up[vertex] = std::min(graphData.up[vertex], graphData.tin[adjective]);
		}
		else {
			DFS_visit(adjective, vertex, graphData);
			graphData.up[vertex] = std::min(graphData.up[vertex], graphData.up[adjective]);
			if (graphData.up[adjective] > graphData.tin[vertex])
				graphData.bridges.push_back(graphData.listOfAdj[vertex][i].second);
		}
	}
}

void findBridges(GraphData & graphData) {
	for (size_t i = 0; i < graphData.getNumberOfVertices(); ++i)
		graphData.visited[i] = false;
	for (size_t i = 0; i < graphData.getNumberOfVertices(); ++i) {
		if (!graphData.visited[i]) {
			DFS_visit(i, i, graphData);
		}
	}
}

int main() {
	int n, m;
	std::cin >> n >> m;
	GraphData graphData(n);
	int firstVertex, secondVertex;
	for (int i = 0; i < m; ++i) {
		std::cin >> firstVertex >> secondVertex;
		try {
			graphData.addEdge(firstVertex - 1, secondVertex - 1);
		}
		catch (std::out_of_range & ex) {
			std::cerr << ex.what() << std::endl;
		}
	}
	findBridges(graphData);
	std::sort(graphData.bridges.begin(), graphData.bridges.end());
	std::cout << graphData.bridges.size() << std::endl;
	for (size_t i = 0; i < graphData.bridges.size(); ++i)
		std::cout << graphData.bridges[i] << ' ';
	std::cout << std::endl;
	return 0;
}