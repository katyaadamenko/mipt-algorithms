#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int INF = std::numeric_limits<int>::max();

class sTree {
	vector<int> tr;
	vector<int> flLog;
public:
	sTree(vector<int> & elements);
	int ans(int l, int r);
	bool isR(int i) {
		return !(i & 1);
	}
	bool isL(int i) {
		return i & 1;
	}
	int parent(int i) {
		return (i - 1) / 2;
	}
};

int fFlLog(int x) {
	if (x == 1)
		return 0;
	else
		return fFlLog(x >> 1) + 1;
}

int findNOD(int x, int y) {
	if (x == INF)
		return y;
	if (y == INF)
		return x;
	if (x == y)
		return x;
	return(x > y ? findNOD(x - y, y) : findNOD(x, y - x));
}

sTree::sTree(vector<int> & elements) {
	int log = fFlLog(elements.size());
	int num = ((1 << log) == elements.size() ? elements.size() : 1 << (log + 1));
	tr.resize(num * 2 - 1, INF);
	flLog.resize(num);
	for (int i = 0; i < num; ++i)
		flLog[i] = fFlLog(i + 1);
	for (int i = 0; i < elements.size(); ++i)
		tr[i + num - 1] = elements[i];
	for (int i = num - 2; i >= 0; --i)
		tr[i] = findNOD(tr[2 * i + 1], tr[2 * i + 2]);
}

int sTree::ans(int l, int r) {
	int num = (tr.size() + 1) >> 1;
	l += num - 1;
	r += num - 1;
	int res = INF;
	while (l <= r) {
		if (l == r) {
			res = findNOD(res, tr[l]);
			break;
		}
		if (isR(l))
			res = findNOD(res, tr[l]);
		l = parent(l + 1);
		if (isL(r))
			res = findNOD(res, tr[r]);
		r = parent(r - 1);
	}
	return res;
}

int main() {
	int n, k;
	std::cin >> n;
	vector<int> elements(n);
	for (int i = 0; i < n; ++i)
		std::cin >> elements[i];
	sTree t(elements);
	std::cin >> k;
	int l, r;
	for (int i = 0; i < k; ++i) {
		std::cin >> l >> r;
		std::cout << t.ans(l - 1, r - 1) << std::endl;
	}

}
