#include <iostream>
#include <string>

using namespace std;

int main()
{
	string a;
	getline(cin, a);
	while (!cin.eof())
	{
		bool inside_word = false;
		int total_words = 0;
		for (unsigned int i = 0; i < a.length(); ++i)
		{
			if ((a[i] >= 65 && a[i] <= 90) || (a[i] >= 97 && a[i] <= 122))
			{
				if (!inside_word)
				{
					++total_words;
					inside_word = true;
				}
			}
			else
			{
				inside_word = false;
			}
		}
		cout << total_words << endl;
		getline(cin, a);
	}
	return 0;
}
