#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> z_func(string s) {
	vector<int> z(s.length());
	z[0] = s.length();
	int l = 0, r = 0;
	for (int i = 1; i < s.length(); ++i) {
		z[i] = (i >= r ? 0 : min(r - i, z[i - l]));
		while (i + z[i] < s.length() && s[i + z[i]] == s[z[i]])
			++z[i];
		if (r <= i + z[i]) {
			r = i + z[i];
			l = i;
		}
	}
	return z;
}

int main() {
	string s, t;
	cin >> s >> t;
	vector<int> z = z_func(t + '#' + s);
	for (size_t i = t.length() + 1; i < z.size(); ++i)
		if (z[i] == t.length())
			cout << i - t.length() - 1 << ' ';
	return 0;
}