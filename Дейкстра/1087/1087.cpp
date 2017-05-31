#include <iostream>
#include <limits>
#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <algorithm>

typedef int vertex_t;
typedef int weight_t;

weight_t findWeightOfShortestPath(const std::map<vertex_t, std::map<vertex_t, weight_t>> & listOfAdj, vertex_t final) {
	std::map<vertex_t, weight_t> distance;
	distance[1] = 0;
	std::priority_queue<std::pair<weight_t, vertex_t>, std::vector<std::pair<weight_t, vertex_t>>, std::greater<std::pair<weight_t, vertex_t>>> q;
	const std::map<vertex_t, weight_t> & distancesFromFirstVertex = listOfAdj.begin()->second;
	for (std::map<vertex_t, weight_t>::const_iterator it = distancesFromFirstVertex.begin(); it != distancesFromFirstVertex.end(); ++it) {
		distance.insert(*it);
		q.push(std::make_pair(distance[it->first], it->first));
	}
	for (size_t i = 0; i < listOfAdj.size() - 1; ++i) {
		vertex_t u;
		weight_t du;
		do {
			u = q.top().second;
			du = q.top().first;
			q.pop();
		} while (du != distance[u]);
		if (u == final)
			break;
		const std::map<vertex_t, weight_t > & adjectivesOfU = listOfAdj.find(u)->second;
		for (std::map<vertex_t, weight_t>::const_iterator it = adjectivesOfU.begin(); it != adjectivesOfU.end(); ++it) {
			if (distance[it->first] > du + it->second) {
				weight_t distanceToAdj = distance[it->first] = du + it->second;
				q.push(std::make_pair(distanceToAdj, it->first));
			}
		}
	}
	return distance[final];
}

int main() {
	vertex_t final;
	weight_t up, down, in, out;
	int numberOfLifts;
	std::cin >> final >> up >> down >> in >> out >> numberOfLifts;
	std::map<vertex_t, std::map<vertex_t, weight_t>> listOfAdj;
	listOfAdj[1].insert(std::make_pair(final, up * (final - 1)));
	listOfAdj[final].insert(std::make_pair(1, down * (final - 1)));
	int numberOfAdjectives;
	std::vector<vertex_t> adjectives;
	vertex_t adjective;
	for (int i = 0; i < numberOfLifts; ++i) {
		adjectives.clear();
		std::cin >> numberOfAdjectives;
		for (int j = 0; j < numberOfAdjectives; ++j) {
			std::cin >> adjective;
			if (listOfAdj.find(adjective) == listOfAdj.end()) {
				for (std::map<vertex_t, std::map<vertex_t, weight_t>>::iterator it = listOfAdj.begin(); it != listOfAdj.end(); ++it) {
					if (it->first != adjective) {
						weight_t distanceFromVertexToAdjective = (it->first < adjective) ? up * (adjective - it->first) : down * (it->first - adjective);
						weight_t distanceFromAdjectiveToVertex = (it->first > adjective) ? up * (it->first - adjective) : down * (adjective - it->first);
						it->second.insert(std::make_pair(adjective, distanceFromVertexToAdjective));
						listOfAdj[adjective].insert(std::make_pair(it->first, distanceFromAdjectiveToVertex));
					}
				}
			}
			for (std::vector<vertex_t>::iterator it = adjectives.begin(); it != adjectives.end(); ++it) {
				std::map<vertex_t, weight_t > ::iterator it1 = listOfAdj[*it].find(adjective);
				std::map<vertex_t, weight_t > ::iterator it2 = listOfAdj[adjective].find(*it);
				if (it1->second > in + out)
					it1->second = in + out;
				if (it2->second > in + out)
					it2->second = in + out;
			}
			adjectives.push_back(adjective);
		}
	}
	std::cout << findWeightOfShortestPath(listOfAdj, final) << std::endl;
	return 0;
}