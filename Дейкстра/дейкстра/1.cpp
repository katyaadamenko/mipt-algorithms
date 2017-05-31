#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <functional>
using namespace std;

typedef int d_t;

const int INF = numeric_limits<int>::max();

int main() {
	int n;
	cin >> n;
	vector<vector<int>> g(n, vector<int>(n));
	vector<int> p(n, -1);
	vector<int> d(n, INF);
	int s, f;
	cin >> s >> f;
	int w;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			cin >> w;
			g[i][j] = (w == -1 ? INF : w);
		}
	--s; --f;
	d[s] = 0;
	p[s] = s;
	priority_queue<pair<d_t, int>, vector<pair<d_t,int>>, greater<pair<d_t, int>>> q;
	q.push(make_pair(d[s], s));
	for (int i = 0; i < n - 1; ++i) {
		int u;
		d_t du;
		do {
			du = q.top().first;
			u = q.top().second;
			q.pop();
		} while (du != d[u]);
		for (int v = 0; v < n; ++v) {
			if (du != INF && g[u][v] != INF && d[v] > du + g[u][v]) {
				d[v] = du + g[u][v];
				p[v] = u;
				q.push(make_pair(d[v], v));
			}
		}
		if (u == f)
			break;
	}
	vector<int> path;
	int u = f, pu = p[f];
	if (d[f] == INF)
		cout << -1 << endl;
	else {

		while (u != pu) {
			path.push_back(u);
			swap(u, pu);
			pu = p[u];
		}
		for (vector<int>::reverse_iterator it = path.rbegin(); it != path.rend(); ++it)
			cout << *it + 1 << ' ';
	}
	return 0;
}