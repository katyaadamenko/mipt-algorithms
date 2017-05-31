#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
#include <functional>

template <typename T, typename Operation, T neutralElement>
class SegmentTree {
	std::vector<T> tree;
	std::vector<int> floorLog;
public:
	SegmentTree(const std::vector<T> & elements);
	int leftChild(int i) {
		/*if (i < 0 || i >= (tree.size()) / 2)
			throw std::out_of_range("Impossible to find left child. Wrong index");*/
		return 2 * i + 1;
	}
	int rightChild(int i) {
		/*if (i < 0 || i >= (tree.size() - 1) / 2)
			throw std::out_of_range("Impossible to find right child. Wrong index");*/
		return 2 * i + 2;
	}
	int parent(int i) {
		/*if (i < 0 || i >= tree.size())
			throw std::out_of_range("Impossible to find parent. Wrong index");*/
		return (i == 0 ? 0 : (i - 1) >> 1);
	}
	T findResult(int leftBound, int rightBound);
	bool isLeftChild(int i) {
		return i & 1;
	}
	bool isRightChild(int i) {
		return !(i & 1);
	}
	void update(int indexOfElement, T newValue);
};

int findFloorLog(int number) {
	/*if (number <= 0)
		throw std::out_of_range("Impossible to find logarithm of a negative number");*/
	if (number == 1)
		return 0;
	return findFloorLog(number >> 1) + 1;
}

template <typename T, typename Operation, T neutralElement>
SegmentTree<T, Operation, neutralElement>::SegmentTree(const std::vector<T> & elements) : floorLog(elements.size()){
	for (size_t i = 0; i < elements.size(); ++i)
		floorLog[i] = findFloorLog(i + 1);
	int nearestPowerOfTwo = 1 << floorLog[elements.size() - 1];
	int numberOfVerticesInTree = 2 * (nearestPowerOfTwo == elements.size() ? nearestPowerOfTwo : nearestPowerOfTwo << 1) - 1;
	tree.resize(numberOfVerticesInTree, neutralElement);
	std::copy(elements.begin(), elements.end(), tree.begin() + (numberOfVerticesInTree + 1) / 2 - 1);
	for (int i = ((numberOfVerticesInTree + 1) >> 1) - 2; i >= 0; --i)
		tree[i] = Operation()(tree[leftChild(i)], tree[rightChild(i)]);
}

template <typename T, typename Operation, T neutralElement>
T SegmentTree<T, Operation, neutralElement>::findResult(int left, int right) {
	/*if (left > right || right >= floorLog.size() || left < 0)
		throw std::out_of_range("Impossible to find minimum. Wrong bound");*/
	T result = neutralElement;
	size_t n = (tree.size() + 1) >> 1;
	left += n - 1;
	right += n - 1;
	while (left <= right) {
		if (left == right) {
			result = Operation()(result, tree[left]);
			break;
		}
		if (isRightChild(left))
			result = Operation()(result, tree[left]);
		left = parent(left + 1);
		if (isLeftChild(right))
			result = Operation()(result, tree[right]);
		right = parent(right - 1);
	}
	return result;
}

template <typename T, typename Operation, T neutralElement>
void SegmentTree<T, Operation, neutralElement>::update(int indexOfElement, T newValue) {
	size_t n = (tree.size() + 1) >> 1;
	indexOfElement += n - 1;
	tree[indexOfElement] = newValue;
	int parentOfElement = parent(indexOfElement);
	while (parentOfElement != indexOfElement) {
		tree[parentOfElement] = Operation()(tree[leftChild(parentOfElement)], tree[rightChild(parentOfElement)]);
		std::swap(parentOfElement, indexOfElement);
		parentOfElement = parent(indexOfElement);
	}
}

/*template <typename Binaryfunction>
class Operation : std::binary_function<T, T, T> {
public:
T operator() (const T & x, const T & y) {
return op(x, y);
}
};

template <typename T, typename BinaryFunction>
class Operation : std::binary_function<T, T, T> {
public:
T operator() (const T & x, const T & y) {
return op(x, y);
}
};*/


int main() {
	int numberOfElements;
	std::cin >> numberOfElements;
	std::vector<long long int> elements;
	elements.reserve(numberOfElements);
	int element;
	for (int i = 0; i < numberOfElements; ++i) {
		std::cin >> element;
		elements.push_back(element);
	}
	SegmentTree<long long int, std::plus<long long int>, 0> tree(elements);
	int numberOfQueries;
	std::cin >> numberOfQueries;
	std::vector<long long int> answers;
	char command;
	int first, second;
	for (int i = 0; i < numberOfQueries; ++i) {
		std::cin >> command >> first >> second;
		if (command == 's')
			answers.push_back(tree.findResult(first - 1, second - 1));
		else
			tree.update(first - 1, second);
	}
	//const int & const(*f) (const int &, const int &) = std::min<int>;
	for (std::vector<long long int>::iterator it = answers.begin(); it != answers.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
	return 0;
}

//(std::ptr_fun(std::min<int>))