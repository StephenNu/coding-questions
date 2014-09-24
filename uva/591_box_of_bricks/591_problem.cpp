#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<int> towers;
	int num_towers;
	int curr_stack;
	int set = 1;
	for (cin >> num_towers; num_towers != 0; cin >> num_towers) {
		towers.clear();
		int num_blocks = 0;
		for (int i = 0; i < num_towers; ++i) {
			cin >> curr_stack;
			num_blocks += curr_stack;
			towers.push_back(curr_stack);
		}
		int final_height = num_blocks / num_towers;
		int moves = 0;
		for (int tower : towers) {
			if (tower < final_height) {
				moves += final_height - tower;
			}
		}
		cout << "Set #" << set << endl;
		cout << "The minimum number of moves is " << moves << "." << endl << endl;
		++set;
	}
	return 0;
}
