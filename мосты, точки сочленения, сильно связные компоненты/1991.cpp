#include <iostream>
#include <vector>
#include <queue>

enum color{WHITE, GRAY, BLACK};
//int time = 0;

class Graph {
	std::vector<std::vector<int> > listOfAdj;
	bool isOriental;
public:
	Graph(int n = 0, bool isOriental = true) : listOfAdj(n, std::vector<int>()), isOriental(isOriental) {}
	void addEdge(int firstVertex, int secondVertex) {
		listOfAdj[firstVertex].push_back(secondVertex);
		if (!isOriental)
			listOfAdj[secondVertex].push_back(firstVertex);
	}
	size_t getNumberOfVertices()const {
		return listOfAdj.size();
	}
	const std::vector<int> & getAdjectives(int i)const {
		return listOfAdj[i];
	}
	Graph findTransposedGraph()const;
};

Graph Graph::findTransposedGraph()const {
	Graph transposedGraph(this->getNumberOfVertices());
	for (size_t i = 0; i < this->getNumberOfVertices(); ++i)
		for (size_t j = 0; j < listOfAdj[i].size(); ++j)
			transposedGraph.listOfAdj[listOfAdj[i][j]].push_back(i);
	return transposedGraph;
}

struct GraphData {
	//std::vector<int> tout;
	std::deque<int> tout; // хранятся вершины в порядке убывания tout
	std::vector<color> colorsOfVertices;
	std::vector<int> numbersOfStronglyConnectedComponent;
	int numberOfStronglyConnectedComponents;
	GraphData(const Graph & graph) :colorsOfVertices(graph.getNumberOfVertices(), WHITE), numbersOfStronglyConnectedComponent(graph.getNumberOfVertices(), -1) {}
};

void DFS_visit_first(int vertex, const Graph & graph, GraphData & graphData) {
	for (size_t j = 0; j < graph.getAdjectives(vertex).size(); ++j) {
		if (graphData.colorsOfVertices[graph.getAdjectives(vertex)[j]] == WHITE) {
			graphData.colorsOfVertices[graph.getAdjectives(vertex)[j]] = GRAY;
			DFS_visit_first(graph.getAdjectives(vertex)[j], graph, graphData);
		}
	}
	graphData.colorsOfVertices[vertex] = BLACK;
	graphData.tout.push_front(vertex);
}

void DFS_first(const Graph & graph, GraphData & graphData) {
	for (size_t i = 0; i < graph.getNumberOfVertices(); ++i)
		graphData.colorsOfVertices[i] = WHITE;
	for (size_t i = 0; i < graph.getNumberOfVertices(); ++i) {
		if (graphData.colorsOfVertices[i] == WHITE) {
			graphData.colorsOfVertices[i] = GRAY;
			DFS_visit_first(i, graph, graphData);
		}
	}
}

void DFS_visit_second(int vertex, const Graph & graph, GraphData & graphData, int numberOfStronglyConnectedComponent) {
	for (size_t j = 0; j < graph.getAdjectives(vertex).size(); ++j) {
		if (graphData.colorsOfVertices[graph.getAdjectives(vertex)[j]] == WHITE) {
			graphData.colorsOfVertices[graph.getAdjectives(vertex)[j]] = GRAY;
			DFS_visit_second(graph.getAdjectives(vertex)[j], graph, graphData, numberOfStronglyConnectedComponent);
		}
	}
	graphData.colorsOfVertices[vertex] = BLACK;
	graphData.numbersOfStronglyConnectedComponent[vertex] = numberOfStronglyConnectedComponent;
}

void DFS_second(const Graph & graph, GraphData & graphData) {
	int numberOfStronglyConnectedComponent = 0;
	for (size_t i = 0; i < graph.getNumberOfVertices(); ++i)
		graphData.colorsOfVertices[i] = WHITE;
	while (!graphData.tout.empty()) {
		int i = graphData.tout.front();
		graphData.tout.pop_front();
		if (graphData.colorsOfVertices[i] == WHITE) {
			++numberOfStronglyConnectedComponent;
			graphData.colorsOfVertices[i] = GRAY;
			DFS_visit_second(i, graph, graphData, numberOfStronglyConnectedComponent);
		}
	}
	graphData.numberOfStronglyConnectedComponents = numberOfStronglyConnectedComponent;
}

std::vector<int> findNumbersOfStronglyConnectedComponent(const Graph & graph, int & numberOfStronglyConnectedComponents) {
	GraphData graphData(graph);
	DFS_first(graph, graphData);
	DFS_second(graph.findTransposedGraph(), graphData);
	numberOfStronglyConnectedComponents = graphData.numberOfStronglyConnectedComponents;
	return graphData.numbersOfStronglyConnectedComponent;
}



int main() {
	int n, m;
	std::cin >> n >> m;
	Graph graph(n);
	int firstVertex, secondVertex;
	for (int i = 0; i < m; ++i) {
		std::cin >> firstVertex >> secondVertex;
		graph.addEdge(firstVertex - 1, secondVertex - 1);
	}
	int numberOfStronglyConnectedComponents = 0;
	std::vector<int> numbersOfStronglyConnectedComponent = findNumbersOfStronglyConnectedComponent(graph, numberOfStronglyConnectedComponents);
	std::cout << numberOfStronglyConnectedComponents << std::endl;
	for (size_t i = 0; i < numbersOfStronglyConnectedComponent.size(); ++i)
		std::cout << numbersOfStronglyConnectedComponent[i] << ' ';
	std::cout << std::endl;
	return 0;
}