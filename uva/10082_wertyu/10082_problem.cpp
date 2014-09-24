#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int main() {

	map<char, char> keyboard = {{'Q', 'Q'}, {'W', 'Q'}, {'E', 'W'}, {'R', 'E'}, {'T', 'R'},
				    {'Y', 'T'}, {'U', 'Y'}, {'I', 'U'}, {'O', 'I'}, {'P', 'O'},
				    {'[', 'P'}, {']', '['}, {'\\', ']'}, {'A', 'A'}, {'S', 'A'},
				    {'D', 'S'}, {'F', 'D'}, {'G', 'F'}, {'H', 'G'}, {'J', 'H'},
				    {'K', 'J'}, {'L', 'K'}, {';', 'L'}, {'\'', ';'}, {'Z', 'Z'},
				    {'X', 'Z'}, {'C', 'X'}, {'V', 'C'}, {'B', 'V'}, {'N', 'B'},
				    {'M', 'N'}, {',', 'M'}, {'.', ','}, {'/', '.'}, {'`', '`'},
				    {'1', '`'}, {'2', '1'}, {'3', '2'}, {'4', '3'}, {'5', '4'},
				    {'6', '5'}, {'7', '6'}, {'8', '7'}, {'9', '8'}, {'0', '9'},
				    {'-', '0'}, {'=', '-'}, {' ', ' '}};
	string input;
	while (getline(cin, input)) {
		for (unsigned int i = 0; i < input.size(); ++i) {
			cout << keyboard[input[i]];
		}
		cout << endl;
	}
	return 0;
}
