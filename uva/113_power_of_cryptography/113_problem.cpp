#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int k;
	double n, p;
	while (cin >> n >> p) {
		k = round(pow(2.0, (log2(p)/n)));
		cout << k << endl;
	}   
	return 0;
}
