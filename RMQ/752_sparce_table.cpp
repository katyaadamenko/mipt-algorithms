#include <iostream>
#include <vector>
#include <algorithm>

typedef int index_t;

template <typename T>
class SparseTable {
	std::vector<std::vector<std::pair<T, index_t>>> table;
	std::vector<int> floorLog;
public:
	SparseTable(const std::vector<T> & elements);
	const std::vector<T> & operator[](size_t i)const {
		return table.at(i);
	}
	std::pair<T, index_t> RMQ(int leftBound, int rightBound)const;
};

int findFloorLog(int number) {
	/*if (number <= 0)
		throw std::out_of_range("Impossible to find logarithm of a negative number");*/
	if (number == 1)
		return 0;
	return findFloorLog(number >> 1) + 1;
}

template <typename T>
SparseTable<T>::SparseTable(const std::vector<T> & elements) : floorLog(elements.size()) {
	for (size_t i = 0; i < elements.size(); ++i)
		floorLog[i] = findFloorLog(i + 1);
	table.resize(floorLog[elements.size() - 1] + 1);
	for (size_t i = 0; i < table.size(); ++i)
		table[i].resize(elements.size());
	for (size_t i = 0; i < elements.size(); ++i)
		table[0][i] = std::make_pair(elements[i], i);
	size_t currentLength = elements.size() - 1;
	for (size_t i = 1; i < table.size(); ++i) {
		for (size_t j = 0; j < currentLength; ++j) {
			table[i][j] = std::max(table[i - 1][j], table[i - 1][j + (1 << i - 1)]);
		}
		currentLength -= (1 << i);
	}
}

template <typename T>
std::pair<T, index_t> SparseTable<T>::RMQ(int leftBound, int rightBound)const {
	/*if (leftBound > rightBound || rightBound >= table[0].size() || leftBound < 0)
		throw std::out_of_range("Impossible to find minimum. Wrong bound");*/
	int k = floorLog[rightBound - leftBound];
	return std::max(table[k][leftBound], table[k][rightBound - (1 << k) + 1]);
}

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
	SparseTable<int> sparseTable(elements);
	int k;
	std::cin >> k;
	int leftBound, rightBound;
	std::pair<int, index_t> answer;
	std::vector<std::pair<int, index_t>> answers;
	answers.reserve(k);
	for (int i = 0; i < k; ++i) {
		std::cin >> leftBound >> rightBound;
		answers.push_back(sparseTable.RMQ(leftBound - 1, rightBound - 1));
	}
	for (int i = 0; i < k; ++i)
		std::cout << answers[i].first << ' ' << answers[i].second + 1 << std::endl;
	return 0;
}
