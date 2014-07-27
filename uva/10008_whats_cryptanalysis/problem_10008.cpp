#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
	vector<pair<char, int>> seen;
	for (char i = 'A'; i <= 'Z'; ++i) {
		seen.push_back(make_pair(i, 0));
	}
	int n;
	cin >> n;
	for (int i = 0; i <= n; ++i) {
		string in;
		getline(cin, in);
		transform(in.begin(), in.end(), in.begin(), std::ptr_fun<int, int>(std::toupper));
		for (unsigned int k = 0; k < in.size(); ++k) {
			if (isalpha(in[k])) {
				++seen[static_cast<int>(in[k] - 'A')].second;
			}
		}
	}
	sort(seen.begin(), seen.end(), 
			[](const pair<char, int>& a, const pair<char, int>& b) {
				if (a.second == b.second) {
					return a.first < b.first;
				} else {
					return a.second > b.second;
				}
			});
	for (unsigned int i = 0; i < seen.size(); ++i) {
		if (seen[i].second != 0) {
			cout << seen[i].first << " " << seen[i].second << endl;
		}
	}
	return 0;
}
