#include <iostream>
#include <vector>
#include <exception>

typedef int time_type;
enum color { WHITE, GRAY, BLACK, RED, BLUE };

class Graph {
	std::vector<std::vector<int> > listOfAdj;
	std::vector<color> colorsOfVertices;
	bool DFS_visit_paint(size_t vertex);
protected:
	size_t DFS_visit(size_t vertex, std::vector<int> & connectedComponent);
public:
	Graph(size_t numberOfVertices = 0) : listOfAdj(numberOfVertices, std::vector<int>()), colorsOfVertices(numberOfVertices, WHITE){}
	size_t getNumberOfVertices()const {
		return listOfAdj.size();
	}
	void addEdge(size_t i, size_t j) {
		//if (i == j || i >= getNumberOfVertices() || j >= getNumberOfVertices())
		//	throw std::out_of_range("Impossible to add edge. Wrong vertices");
		listOfAdj[i].push_back(j);
		listOfAdj[j].push_back(i);
	}
	std::vector<std::vector<int> > DFS();
	bool chromaticNumberIsTwo();
	std::vector<color> getColors()const {
		return colorsOfVertices;
	}
};

size_t Graph::DFS_visit(size_t vertex, std::vector<int> & connectedComponent) {
	static int numberOfVerticesInTree = 1;
	connectedComponent.push_back(vertex);
	colorsOfVertices[vertex] = GRAY;
	std::vector<std::vector<int>>::iterator it1 = listOfAdj.begin() + vertex;
	for (std::vector<int>::iterator it = it1->begin();
		it != it1->end(); ++it) {
		if (colorsOfVertices[*it] == WHITE) {
			++numberOfVerticesInTree;
			DFS_visit(*it, connectedComponent);
		}
	}
	colorsOfVertices[vertex] = BLACK;
	return numberOfVerticesInTree;
}

std::vector<std::vector<int>> Graph::DFS() {
	std::vector<std::vector<int>> forest;
	for (std::vector<color> ::iterator it = colorsOfVertices.begin(); it != colorsOfVertices.end(); ++it)
		*it = WHITE;
	for (size_t i = 0; i < getNumberOfVertices(); ++i) {
		if (colorsOfVertices[i] == WHITE) {
			forest.push_back(std::vector<int>());
			DFS_visit(i, *(forest.end() - 1));
		}
	}
	return forest;
}

bool Graph::chromaticNumberIsTwo() {
	bool possibleToPaint = true;
	for (std::vector<color> ::iterator it = colorsOfVertices.begin(); it != colorsOfVertices.end(); ++it)
		*it = WHITE;
	for (size_t i = 0; i < getNumberOfVertices(); ++i) {
		if (colorsOfVertices[i] == WHITE) {
			colorsOfVertices[i] = RED;
			possibleToPaint = DFS_visit_paint(i);
		}
		if (!possibleToPaint)
			break;
	}
	return possibleToPaint;
}

bool Graph::DFS_visit_paint(size_t vertex) {
	bool possibleToPaint = true;
	color colorOfAdjectives;
	if (colorsOfVertices[vertex] == RED)
		colorOfAdjectives = BLUE;
	else
		colorOfAdjectives = RED;
	std::vector<std::vector<int>> ::iterator it1 = listOfAdj.begin() + vertex;
	for (std::vector<int>::iterator it = it1->begin(); it != it1->end(); ++it) {
		if (colorsOfVertices[*it] != WHITE && colorsOfVertices[*it] != colorOfAdjectives) {
			possibleToPaint = false;
			break;
		}
		if (colorsOfVertices[*it] == WHITE) {
			colorsOfVertices[*it] = colorOfAdjectives;
			possibleToPaint = DFS_visit_paint(*it);
		}
		if (!possibleToPaint)
			break;
	}
	return possibleToPaint;
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
	if (graph.chromaticNumberIsTwo()) {
		std::cout << "YES" << std::endl;
		std::vector<color> coloringOfVertices = graph.getColors();
		for (size_t i = 0; i < coloringOfVertices.size(); ++i)
			if (coloringOfVertices[i] == RED)
				std::cout << (i + 1) << ' ';
		std::cout << std::endl;
	}
	else
		std::cout << "NO" << std::endl;
	return 0;
}