#include <iostream>
#include <vector>
using namespace std;

class sTr {
	vector<long long> t;
public:
	sTr(vector<long long> & elements);
	void add(int l, int r, int ad);
	long long get(int i);
	bool isL(int i) {
		return (i & 1);
	}
	bool isR(int i) {
		return !(i & 1);
	}
	int parent(int i) {
		return i > 0 ? (i - 1) / 2 : 0;
	}
};

int fFlLog(int i) {
	if (i == 1)
		return 0;
	return fFlLog(i >> 1) + 1;
}

sTr::sTr(vector<long long> & elements) {
	int log = fFlLog(elements.size());
	int num = ((1 << log) == elements.size() ? 1 << log : 1 << (log + 1));
	t.resize(2 * num - 1, 0);
	for (int i = 0; i < elements.size(); ++i)
		t[i + num - 1] = elements[i];
}

void sTr::add(int l, int r, int ad) {
	int n = (t.size() + 1) >> 1;
	l += n - 1;
	r += n - 1;
	while (l <= r) {
		if (l == r) {
			t[l] += ad;
			break;
		}
		if (isR(l))
			t[l] += ad;
		l = parent(l + 1);
		if (isL(r))
			t[r] += ad;
		r = parent(r - 1);
 	}
}

long long sTr::get(int i) {
	int num = (t.size() + 1) / 2;
	i += num - 1;
	long long res = 0;
	while (i > 0) {
		res += t[i];
		i = parent(i);
	}
	res += t[0];
	return res;
}

int main() {
	int n;
	cin >> n;
	vector<long long> elements(n);
	for (int i = 0; i < n; ++i) {
		cin >> elements[i];
	}
	sTr tree(elements);
	int k;
	cin >> k;
	char c;
	int l, r, ad;
	for (int i = 0; i < k; ++i) {
		cin >> c;
		if (c == 'a') {
			cin >> l >> r >> ad;
			tree.add(l - 1, r - 1, ad);
		}
		else {
			cin >> ad;
			std::cout << tree.get(ad - 1) << std::endl;
		}
	}
	return 0;
}