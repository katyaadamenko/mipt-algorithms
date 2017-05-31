#include <iostream>
#include <vector>

typedef int weight_t;

class DSU {
	std::vector<int> parentsOfElements;
	std::vector<int> numberOfElementsInTrees;
	std::vector<int> weightOfTrees;
public:
	DSU(int numberOfElements = 0) {
		parentsOfElements.reserve(numberOfElements);
		numberOfElementsInTrees.reserve(numberOfElements);
		weightOfTrees.reserve(numberOfElements);
		for (int i = 0; i < numberOfElements; ++i)
			make_set();
	}
	void make_set() {
		parentsOfElements.push_back(parentsOfElements.size());
		numberOfElementsInTrees.push_back(1);
		weightOfTrees.push_back(0);
	}
	int find_set(int x) {
		if (parentsOfElements.at(x) != x)
			return parentsOfElements.at(x) = find_set(parentsOfElements.at(x));
		return x;
	}
	void union_sets(int x, int y, weight_t weight);
	weight_t getWeightOfTree(int x) {
		return weightOfTrees.at(x);
	}
};

void DSU::union_sets(int x, int y, weight_t weight) {
	x = find_set(x);
	y = find_set(y);
	if (x != y) {
		if (numberOfElementsInTrees[y] > numberOfElementsInTrees[x])
			std::swap(x, y);
		parentsOfElements[y] = x;
		numberOfElementsInTrees[x] += numberOfElementsInTrees[y];
		weightOfTrees[x] += weightOfTrees[y] + weight;
	}
	else
		weightOfTrees[x] += weight;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	DSU dsu(n);
	char command;
	int first, second;
	weight_t weight;
	for (int i = 0; i < m; ++i) {
		std::cin >> command;
		if (command == '1') {
			std::cin >> first >> second >> weight;
			dsu.union_sets(first - 1, second - 1, weight);
		}
		else {
			std::cin >> first;
			std::cout << dsu.getWeightOfTree(dsu.find_set(first - 1)) << std::endl;
		}
	}
	return 0;
}