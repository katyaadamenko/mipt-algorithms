#include <iostream>
#include <vector>

typedef int index_t;

class BinaryIndexedTree {
	std::vector<long long int> tree;
public:
	BinaryIndexedTree(const std::vector<long long int> & elements): tree(elements.size(), 0) {
		for (size_t i = 0; i < elements.size(); ++i)
			update(i, elements[i]);
	}
	void update(index_t i,long long int addition) {
		while (i < tree.size()) {
			tree[i] += addition;
			i = i | (i + 1);
		}
	}
	long long int sum(index_t i)const {
		long long int result = 0;
		while (i >= 0) {
			result += tree[i];
			i = (i & (i + 1)) -1;
		}
		return result;
	}
	long long int RSQ(index_t i, index_t j)const {
		return sum(j) - sum(i - 1);
	}
};

int main() {
	int n;
	std::cin >> n;
	std::vector<long long int> elements(n);
	for (std::vector<long long int>::iterator it = elements.begin(); it != elements.end(); ++it)
		std::cin >> *it;
	BinaryIndexedTree tree(elements);
	int m; 
	std::cin >> m;
	char command;
	int first, second;
	std::vector<long long int> answers;
	for (int i = 0; i < m; ++i) {
		std::cin >> command >> first >> second;
		if (command == 's') {
			answers.push_back(tree.RSQ(first - 1, second - 1));
		}
		else {
			tree.update(first - 1, second - elements[first - 1]);
			elements[first - 1] = second;
		}
	}
	for (std::vector<long long int>::iterator it = answers.begin(); it != answers.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
	return 0;
}