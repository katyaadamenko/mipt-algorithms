#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int INF = 30000;

struct Edge {
	int u, v;
	int w;
	Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

bool relax(Edge e, vector<int> & d) {
	if (d[e.u] != INF && d[e.v] > d[e.u] + e.w) {
		d[e.v] = d[e.u] + e.w;
		return true;
	}
	return false;
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<Edge> g;
	g.reserve(n);
	int u, v, w;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		g.push_back(Edge(u - 1, v - 1, w));
	}
	vector<int> d(n, INF);
	d[0] = 0;
	for (int i = 0; i < n - 1; ++i) {
		for (vector<Edge>::iterator it = g.begin(); it != g.end(); ++it)
			relax(*it, d);
	}
	for (vector<int>::iterator it = d.begin(); it != d.end(); ++it)
		cout << *it << ' ';
	cout << endl;
	return 0;
}
