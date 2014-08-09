#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct block {
	block(int num_, block* prev_, block* next_)
		: num(num_), prev(prev_), next(next_) {}
	int num;
	block* prev;
	block* next;
};

void ResetBlock(block* to_reset) {
	block* temp = nullptr;
	for (block* it = to_reset; it != nullptr; it = temp) {
		temp = it->next;
		it->next = nullptr;
		if (it->prev != nullptr) {
			it->prev->next = nullptr;
			it->prev = nullptr;
		}
	}
}

bool ValidCmd(block* dest, block* src) {
	block* it = nullptr;
	for (it = src; it != nullptr; it = it->next) {
		if (it->num == dest->num) {
			return false;
		}
	}
	for (it = dest; it != nullptr; it = it->next) {
		if (it->num == src->num) {
			return false;
		}
	}
	return true;
}

void PlaceOnTop(block* dest, block* src) {
	block* it = nullptr;
	if (src->prev != nullptr) {
		src->prev->next = nullptr;
	}
	for (it = dest; it->next != nullptr; it = it->next);
	it->next = src;
	src->prev = it;
}

void PrintBoard(vector<block>& blocks) {
	for (unsigned int i = 0; i < blocks.size(); ++i) {
		cout << i << ":";
		if (blocks[i].prev == nullptr) {
			for (block* it = &blocks[i]; it != nullptr; it = it->next) {
				cout << " " << it->num;
			}
		}
		cout << '\n';
	}
}

int main() {
	int num_blocks;
	vector<block> blocks;
	cin >> num_blocks;
	for (int i = 0; i < num_blocks; ++i) {
		blocks.push_back(block(i, nullptr, nullptr));
	}
	string cmd;
	for (cin >> cmd; cmd != "quit"; cin >> cmd) {
		int src, dest;
		string cmd2;
		cin >> src >> cmd2 >> dest;
		if (!ValidCmd(&blocks[dest], &blocks[src])) {
			continue;
		}
		if (cmd[0] == 'm' && cmd2[1] == 'n') { // move onto
			ResetBlock(blocks[dest].next);
			ResetBlock(blocks[src].next);
			PlaceOnTop(&blocks[dest], &blocks[src]);
		} else if (cmd[0] == 'm') { // move over
			ResetBlock(blocks[src].next);
			PlaceOnTop(&blocks[dest], &blocks[src]);
		} else if (cmd2[1] == 'n') { // pile onto
			ResetBlock(blocks[dest].next);
			PlaceOnTop(&blocks[dest], &blocks[src]);
		} else { // pile over
			PlaceOnTop(&blocks[dest], &blocks[src]);
		}
	}
	PrintBoard(blocks);
	return 0;
}
