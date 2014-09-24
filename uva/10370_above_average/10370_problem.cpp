#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
	vector<double> marks;
	int C, N;
	cin >> C;
	for (int i = 0; i < C; ++i) {
		double average = 0.0;
		double mark;
		double over_avg = 0.0;
		cin >> N;
		for (int k = 0; k < N; ++k) {
			cin >> mark;
			average += mark;
			marks.push_back(mark);
		}
		average /= N;
		for (const auto& m : marks) {
			if (m > average) {
				++over_avg;
			}
		}
		marks.clear();
		cout << fixed << setprecision(3) << (100*(over_avg/N)) << "%" << endl;
	}
	return 0;
}
