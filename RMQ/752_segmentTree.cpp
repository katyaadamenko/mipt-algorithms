#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
#include <functional>
#include <climits>

typedef int index_t;

const int _INF = -2000000000;

template <typename T, typename Operation, T neutralElement>
class SegmentTree {
	std::vector<std::pair<T, index_t>> tree;
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
		return (i == 0 ? 0 : (i - 1) / 2);
	}
	std::pair<T, index_t> findResult(int leftBound, int rightBound);
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
	return findFloorLog (number >> 1) + 1;
}

template <typename T, typename Operation, T neutralElement>
SegmentTree<T, Operation, neutralElement>::SegmentTree(const std::vector<T> & elements) : floorLog(elements.size()){
	Operation op;
	for (size_t i = 0; i < elements.size(); ++i)
		floorLog[i] = findFloorLog(i + 1);
	int nearestPowerOfTwo = 1 << floorLog[elements.size() - 1];
	int numberOfVerticesInTree = 2 * (nearestPowerOfTwo == elements.size() ? nearestPowerOfTwo : nearestPowerOfTwo << 1) - 1;
	tree.resize(numberOfVerticesInTree, std::make_pair(neutralElement, -1));
	int n = (numberOfVerticesInTree + 1) >> 1;
	//std::copy(elements.begin(), elements.end(), tree.begin() + (numberOfVerticesInTree + 1) / 2 - 1);
	for (size_t i = 0; i < elements.size(); ++i)
		tree[i + n - 1] = std::make_pair(elements[i], i);
	T value;
	index_t index;
	for (int i = n - 2; i >= 0; --i) {
		value = op(tree[leftChild(i)].first, tree[rightChild(i)].first);
		index = (value == tree[leftChild(i)].first ? tree[leftChild(i)].second : tree[rightChild(i)].second);
		tree[i] = std::make_pair(value, index);
	}
}

template <typename T, typename Operation, T neutralElement>
std::pair<T, index_t> SegmentTree<T, Operation, neutralElement>::findResult(int left, int right) {
	/*if (left > right || right >= floorLog.size() || left < 0)
	throw std::out_of_range("Impossible to find minimum. Wrong bound");*/
	Operation op;
	T value = neutralElement;
	index_t index = -1;
	size_t n = (tree.size() + 1) >> 1;
	left += n - 1;
	right += n - 1;
	while (left <= right) {
		if (left == right) {
			value = op(value, tree[left].first);
			if (value == tree[left].first)
				index = tree[left].second;
			break;
		}
		if (isRightChild(left)) {
			value = op(value, tree[left].first);
			if (value == tree[left].first)
				index = tree[left].second;
		}
		left = parent(left + 1);
		if (isLeftChild(right)) {
			value = op(value, tree[right].first);
			if (value == tree[right].first)
				index = tree[right].second;
		}
		right = parent(right - 1);
	}
	std::pair<T, index_t> result = std::make_pair(value, index);
	return result;
}

template <typename T, typename Operation, T neutralElement>
void SegmentTree<T, Operation, neutralElement>::update(int indexOfElement, T newValue) {
	Operation op;
	size_t n = (tree.size() + 1) >> 1;
	indexOfElement += n - 1;
	tree[indexOfElement] = newValue;
	int parentOfElement = parent(indexOfElement);
	T value;
	index_t index;
	while (parentOfElement != indexOfElement) {
		value = op(tree[leftChild(parentOfElement)].first, tree[rightChild(parentOfElement)].first);
		index = (value == tree[leftChild(parentOfElement)].first ? tree[leftChild(parentOfElement)].second : tree[rightChild(parentOfElement)].second);
		tree[parentOfElement] = std::make_pair(value, index);
		std::swap(parentOfElement, indexOfElement);
		parentOfElement = parent(indexOfElement);
	}
}

template <typename T>
class MyMin : std::binary_function<T, T, T> {
public:
	T operator()(const T & x, const T & y) {
		return std::min(x, y);
	}
};

template <typename T>
class MyMax : std::binary_function<T, T, T> {
public:
	T operator()(const T & x, const T & y) {
		return std::max(x, y);
	}
};

int main() {
	int n;
	std::cin >> n;
	std::vector<int> elements;
	elements.reserve(n);
	int element;
	for (int i = 0; i < n; ++i) {
		std::cin >> element;
		elements.push_back(element);
	}
	SegmentTree<int, MyMax<int>, _INF> segmentTree(elements);
	int k;
	std::cin >> k;
	int leftBound, rightBound;
	std::pair<int, index_t> answer;
	std::vector<std::pair<int, index_t>> answers;
	answers.reserve(k);
	for (int i = 0; i < k; ++i) {
		std::cin >> leftBound >> rightBound;
		answers.push_back(segmentTree.findResult(leftBound - 1, rightBound - 1));
	}
	for (int i = 0; i < k; ++i)
		std::cout << answers[i].first << ' ' << answers[i].second + 1 << std::endl;
	return 0;
}
