#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

typedef int index_t;

class BinaryIndexedTree {
	std::vector<std::vector<long int>> tree;
public:
	BinaryIndexedTree(const std::vector<std::vector<long int>> & elements) : tree(elements.size(), std::vector<long int>(elements[0].size(), 0)) {
		for (size_t i = 0; i < elements.size(); ++i)
			for (size_t j = 0; j < elements[0].size(); ++j)
				update(i, j, elements[i][j]);
	}
	BinaryIndexedTree(size_t n, size_t m) : tree(n, std::vector<long int>(m, 0)) {}
	void update(index_t i, index_t j, int addition = 1) {
		for (size_t k = i; k < tree.size(); k = k | (k + 1))
			for (size_t l = j; l < tree[0].size(); l = l | (l + 1))
				tree[k][l] += addition;
	}
	long long int sum(index_t i, index_t j) {
		long long result = 0;
		for (index_t k = i; k >= 0; k = (k & (k + 1)) - 1)
			for (index_t l = j; l >= 0; l = (l & (l + 1)) - 1)
				result += tree[k][l];
		return result;
	}
	long long RSQ(index_t x1, index_t y1, index_t x2, index_t y2) {
		index_t xMax = std::max(x1, x2);
		index_t xMin = (xMax == x1 ? x2 : x1);
		index_t yMax = std::max(y1, y2);
		index_t yMin = (yMax == y1 ? y2 : y1);
		return sum(xMax, yMax) - sum(xMax, yMin - 1) - sum(xMin - 1, yMax) + sum(xMin - 1, yMin - 1);
	}
};

int main() {
	int n, m;
	std::cin >> n >> m;
	//std::vector<long long> answers;
	std::string command;
	index_t first, second;
	index_t x1, y1, x2, y2;
	BinaryIndexedTree tree(n, n);
	for (int i = 0; i < m; ++i) {
		std::cin >> command;
		if (command == "ADD") {
			std::cin >> first >> second;
			tree.update(first - 1, second - 1);
		}
		else {
			std::cin >> x1 >> y1 >> x2 >> y2;
			std::cout << tree.RSQ(x1 - 1, y1 - 1, x2 - 1, y2 - 1) << std::endl;
			//answers.push_back(tree.RSQ(x1 - 1, y1 - 1, x2 - 1, y2 - 1));
		}
	}
	//for (std::vector<long long>::iterator it = answers.begin(); it != answers.end(); ++it)
	//	std::cout << *it << std::endl;
	return 0;
}