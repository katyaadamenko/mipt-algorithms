#include <iostream>
#include <vector>

void DFS_visit(int i, int j, std::vector<std::vector<char>> & v) {
	v[i][j] = '.';
	if (v[i + 1][j] == '#')
		DFS_visit(i + 1, j, v);
	if (v[i - 1][j] == '#')
		DFS_visit(i - 1, j, v);
	if (v[i][j - 1] == '#')
		DFS_visit(i, j - 1, v);
	if (v[i][j + 1] == '#')
		DFS_visit(i, j + 1, v);
}

int numberOfPieces(std::vector<std::vector<char>> v) {
	int numberOfPieces = 0;
	for (size_t i = 1; i < v.size() - 1; ++i)
		for (size_t j = 1; j < v[0].size() - 1; ++j)
			if (v[i][j] == '#') {
				DFS_visit(i, j, v);
				++numberOfPieces;
			}
	return numberOfPieces;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<char>> v(n + 2, std::vector<char>(m + 2));
	for (int i = 1; i < n + 1; ++i)
		for (int j = 1; j < m + 1; ++j)
			std::cin >> v[i][j];
	for (int i = 0; i < n + 2; ++i) {
		v[i][0] = '.';
		v[i][m + 1] = '.';
	}
	for (int j = 0; j < m + 2; ++j) {
		v[0][j] = '.';
		v[n + 1][j] = '.';
	}
	std::cout << numberOfPieces(v) << std::endl;
	return 0;
}