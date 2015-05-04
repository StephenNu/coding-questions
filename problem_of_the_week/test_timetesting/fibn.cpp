#include <iostream>
#include <vector>

using namespace std;
vector<long> fibs;
long fib(int n) {
  int i = fibs.size();
  for (; i < n; ++i) {
    fibs.push_back(fibs[i-1] + fibs[i-2]);
  }
  return fibs[n-1];
}

int main() {
  fibs.push_back(1);
  fibs.push_back(1);
  int n;
  cin >> n;
  cout << fib(n) << endl;
}
