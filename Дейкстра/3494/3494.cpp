#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <functional>

typedef int vertex_t;
typedef int weight_t;

const int INF = std::numeric_limits<int>::max();

struct AdjectiveData {
	vertex_t adjective;
	weight_t weightOfEdge;
	AdjectiveData(vertex_t adjective, weight_t weightOfEdge) : adjective(adjective), weightOfEdge(weightOfEdge) {}
};

std::vector<weight_t> findDistances(const std::vector<std::vector<AdjectiveData>> & listOfAdj, vertex_t source) {
	std::vector<weight_t> distance(listOfAdj.size(), INF);
	distance[source] = 0;
	std::priority_queue<std::pair<weight_t, vertex_t>, std::vector<std::pair<weight_t, vertex_t>>, std::greater<std::pair<weight_t, vertex_t>>> q;
	q.push(std::make_pair(distance[source], source));
	for (size_t i = 0; i < listOfAdj.size(); ++i) {
		vertex_t u;
		weight_t du;
		do {
			u = q.top().second;
			du = q.top().first;
			q.pop();
		} while (distance[u] != du && !q.empty());
		if (distance[u] != du && q.empty())
			break;
		for (std::vector<AdjectiveData>::const_iterator it = listOfAdj[u].begin(); it != listOfAdj[u].end(); ++it)
			if (distance[u] != INF && distance[it->adjective] > distance[u] + it->weightOfEdge) {
				distance[it->adjective] = distance[u] + it->weightOfEdge;
				q.push(std::make_pair(distance[it->adjective], it->adjective));
			}
	}
	return distance;
}

int main() {
	int num;
	std::cin >> num;
	for (int k = 0; k < num; ++k) {
		int n, m;
		vertex_t source;
		std::cin >> n >> m;
		std::vector<std::vector<AdjectiveData>> listOfAdj(n, std::vector<AdjectiveData>());
		vertex_t first, last;
		weight_t weightOfEdge;
		for (int i = 0; i < m; ++i) {
			std::cin >> first >> last >> weightOfEdge;
			listOfAdj.at(first).push_back(AdjectiveData(last, weightOfEdge));
			listOfAdj.at(last).push_back(AdjectiveData(first, weightOfEdge));
		}
		std::cin >> source;
		std::vector<weight_t> distances;
		distances = findDistances(listOfAdj, source);
		for (std::vector<weight_t>::iterator it = distances.begin(); it != distances.end(); ++it)
			std::cout << (*it != INF ? *it : 2009000999) << ' ';
		std::cout << std::endl;
	}
	return 0;
}