#include <iostream>
#include <vector>
#include <queue>
#include <limits>

enum color{WHITE, GRAY, BLACK};
const int dx[4] = { 1, 0, -1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

typedef std::vector<std::vector<int>> table_t;
typedef std::vector<std::vector<color>> table_of_colors_t;
typedef int height_t;
typedef int width_t;

table_t findTableOfShortestPaths(const table_t & table) {
	int height = table.size();
	int width = table[0].size();
	table_of_colors_t tableOfColors(height, std::vector<color>(width, WHITE));
	table_t tableOfShortestPaths(height, std::vector<int>(width));
	table_t tableOfDistances(height, std::vector<int>(width, 0));
	std::queue<std::pair<height_t, width_t>> Q;
	int x, y;
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j) {
			if (i || j)
				for (int i = 0; i < height; ++i)
					for (int j = 0; j < width; ++j) {
						tableOfColors[i][j] = WHITE;
						tableOfDistances[i][j] = 0;
					}
			if (table[i][j] == 0) {
				tableOfColors[i][j] = GRAY;
				Q.push(std::make_pair(i, j));
				while (!Q.empty()) {
					std::pair<height_t, width_t> nextElement = Q.front();
					Q.pop();
					for (int k = 0; k < 4; ++k) {
						x = nextElement.first + dx[k];
						y = nextElement.second + dy[k];
						if (x >= 0 && y >= 0 && x < height && y < width && tableOfColors[x][y] == WHITE) {
							tableOfColors[x][y] = GRAY;
							tableOfDistances[x][y] = tableOfDistances[nextElement.first][nextElement.second] + 1;
							Q.push(std::make_pair(x, y));
							if (table[x][y] == 1) {
								tableOfShortestPaths[i][j] = tableOfDistances[x][y];
								break;
							}
						}
					}
					if (tableOfShortestPaths[i][j] != 0) {
						while (!Q.empty())
							Q.pop();
						break;
					}
				}
			}
		}
	return tableOfShortestPaths;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	table_t table(n, std::vector<int>(m));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			std::cin >> table[i][j];
	table_t tableOfShortestPaths = findTableOfShortestPaths(table);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			std::cout << tableOfShortestPaths[i][j] << ' ';
		std::cout << std::endl;
	}
	return 0;	
}