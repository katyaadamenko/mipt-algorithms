#include <iostream>
#include <vector>

typedef int index_t;

class BinaryIndexedTree {
	std::vector<long long> tree;
public:
	BinaryIndexedTree(size_t numberOfElements) : tree(numberOfElements, 0) {}
	BinaryIndexedTree(const std::vector<long long> & elements) : tree(elements.size(), 0) {
		for (size_t i = 0; i < elements.size(); ++i)
			update(i, elements[i]);
	}
	void update(index_t i, int addition) {
		while (i < tree.size()) {
			tree[i] += addition;
			i = i | (i + 1);
		}
	}
	long long sum(index_t i) {
		long long result = 0;
		while (i >= 0) {
			result += tree[i];
			i = (i & (i + 1)) - 1;
		}
		return result;
	}
	long long RSQ(index_t left, index_t right) {
		return sum(right) - sum(left - 1);
	}
};

int main() {
	int n;
	std::cin >> n;
	BinaryIndexedTree tree(n);
	char command;
	std::cin >> command;
	index_t i, left, right;
	int addition;
	while (command - '0') {
		if (command == '1') {
			std::cin >> i >> addition;
			tree.update(i - 1, addition);
		}
		else {
			std::cin >> left >> right;
			std::cout << tree.RSQ(left - 1, right - 1) << std::endl;
		}
		std::cin >> command;
	}
	return 0;
}