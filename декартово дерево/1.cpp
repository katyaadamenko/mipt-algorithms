#include <iostream>
#include <vector>
using namespace std;

class Treap {
	int x;
	int y;
	Treap * l;
	Treap * r;
public:
	Treap(int x, Treap * l = nullptr, Treap * r = nullptr) : x(x), l(l), r(r) {
		y = rand() * rand();
	}
	~Treap() {
		if (!l)
			delete l;
		if (!r)
			delete r;
	}
	int getX() {
		return x;
	}
	friend Treap * merge(Treap * L, Treap * R);
	friend pair<Treap *, Treap *> split(Treap * T, int x0);
	friend Treap * add( Treap * T, int i);
	friend Treap * next(Treap * T, int i);
};

Treap * merge(Treap * L, Treap * R) {
	Treap * T;
	if (!L)
		return R;
	if (!R)
		return L;
	if (L->y > R->y) {
		T = L;
		T->r = merge(L->r, R);
	}
	else {
		T = R;
		T->l = merge(L, R->l);
	}
	return T;
}

pair<Treap *, Treap *> split(Treap * T, int x0) {
	if (!T)
		return make_pair(T, T);
	Treap * L, *R;
	pair<Treap*, Treap *> res;
	if (T->x <= x0) {
		L = T;
		res = split(L->r, x0);
		L->r = res.first;
		R = res.second;
	}
	else {
		R = T;
		res = split(T->l, x0);
		L = res.first;
		R->l = res.second;
	}
	return make_pair(L, R);
}

Treap * add(Treap * T, int i) {
	Treap * L, *M, *R;
	pair<Treap *, Treap *> res;
	res = split(T, i - 1);
	L = res.first;
	res = split(res.second, i);
	M = res.first;
	R = res.second;
	if (!M)
		M = new Treap(i);
	return merge(L, merge(M, R));
}

Treap * next(Treap * T, int i) {
	Treap * res = nullptr;
	bool found = 0;
	Treap * cur = T, *prev = nullptr;
	while (cur && !found) {
		if (cur->x < i) {
			prev = cur;
			cur = cur->r;
		}
		else if (cur->x == i) {
			res = cur;
			found = 1;
		}
		else {
			res = cur;
			prev = cur;
			cur = cur->l;
		}
	}
	return res;
}

int main() {
	int n;
	std::cin >> n;
	Treap * treap = nullptr;
	long previousResult = 0;
	bool previousCommandWasNext = false;
	char command;
	int value;
	std::vector<int> answers;
	for (int i = 0; i < n; ++i) {
		std::cin >> command >> value;
		if (command == '+') {
			if (previousCommandWasNext)
				value = (value + previousResult) % ((int)1E9);
			treap = add(treap, value);
			previousCommandWasNext = false;
		}
		else {
			Treap * res = next(treap, value);
			previousResult = (res ? res->getX() : -1);
			answers.push_back(previousResult);
			previousCommandWasNext = true;
		}
	}
	for (std::vector<int>::iterator it = answers.begin(); it != answers.end(); ++it)
		std::cout << *it << std::endl;
	return 0;
}