#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> findNextPermutation(const std::vector<int> & permutation) {
	std::vector<int> nextPermutation(permutation);
	bool isDecreasing = true;
	for (size_t i = permutation.size() - 1; i > 0; --i) {
		if (nextPermutation[i] > nextPermutation[i - 1]) {
			for (size_t j = permutation.size() - 1; j >= i; --j)
				if (nextPermutation[j] > nextPermutation[i - 1]) {
					std::swap(nextPermutation[j], nextPermutation[i - 1]);
					std::sort(nextPermutation.begin() + i, nextPermutation.end());
					isDecreasing = false;
					break;
				}
			if (!isDecreasing)
				break;
		}
	}
	if (isDecreasing) {
		if (nextPermutation[0] != permutation.size()) {
			++nextPermutation[0];
			for (size_t i = 1; i < permutation.size(); ++i)
				i < nextPermutation[0] ? nextPermutation[i] = i : nextPermutation[i] = i + 1;
		}
		else
			for (size_t i = 0; i < permutation.size(); ++i)
				nextPermutation[i] = i + 1;
	}
	return nextPermutation;
}

int main() {
	int n;
	std::cin >> n;
	std::vector<int> permutation;
	permutation.reserve(n);
	int element;
	for (int i = 0; i < n; ++i) {
		std::cin >> element;
		permutation.push_back(element);
	}
	permutation = findNextPermutation(permutation);
	for (int i = 0; i < n; ++i)
		std::cout << permutation[i] << ' ';
	std::cout << std::endl;
	return 0;
}