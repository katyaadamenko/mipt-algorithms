#include <iostream>
#include <vector>

int main() {
	int n;
	int m;
	std::cin >> n >> m;
	std::vector<int> numberOfAdgectives(n, 0);
	size_t firstVertice, secondVertice;
	for (int i = 0; i < m; ++i) {
		std::cin >> firstVertice >> secondVertice;
		++numberOfAdgectives.at(firstVertice - 1);
		++numberOfAdgectives.at(secondVertice - 1);
	}
	int value = numberOfAdgectives[0];
	bool isRegular = true;
	int i = 1;
	while (i < n && isRegular) {
		if (numberOfAdgectives[i] != value)
			isRegular = false;
		++i;
	}
	isRegular ? (std::cout << "YES") : (std::cout << "NO");
	std::cout << std::endl;
	return 0;
}