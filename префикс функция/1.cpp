#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> p_func(string s) {
	vector<int> p(s.length());
	p[0] = 0;
	for (int i = 1; i < s.length(); ++i) {
		int prV = p[i - 1];
		while (s[prV] != s[i] && prV > 0)
			prV = p[prV - 1];
		if (prV == 0 && s[0] != s[i])
			p[i] = 0;
		else
			p[i] = prV + 1;
	}
	return p;
}

int main() {
	string s;
	cin >> s;
	vector<int> p = p_func(s);
	for (int i = 0; i < s.length(); ++i)
		cout << p[i] << ' ';
	cout << endl;
	return 0;
}