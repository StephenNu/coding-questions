#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
  int m, n;
  while (cin >> m >> n) {
    vector<int> a;
    int temp;
    for (int i = 0; i < m + n; ++i) {
      cin >> temp;
      a.push_back(temp);
    }
    sort(a.begin(), a.end());
    int k = a.size()/2;
    if (a.size()%2 == 0) {
      cout << fixed << setprecision(1) << static_cast<double>((a[k] + a[k-1])/2.0) << endl;
    } else {
      cout << fixed << setprecision(1) << static_cast<double>(a[k]) << endl;
    }
  }
  return 0;
}
