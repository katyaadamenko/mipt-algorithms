#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> pr_f(string & s) {
	vector<int> pr(s.length());
	pr[0] = 0;
	for (int i = 1; i < s.length(); ++i) {
		int prVal = pr[i - 1];
		while (s[prVal] != s[i] && prVal > 0)
			prVal = pr[prVal - 1];
		if (prVal == 0 && s[0] != s[i])
			pr[i] = 0;
		else
			pr[i] = prVal + 1;
	}
	return pr;
}

int main() {
	string s;
	cin >> s;
	vector<int> pr = pr_f(s);
	cout << s.length() - pr[s.length() - 1];
	return 0;
}