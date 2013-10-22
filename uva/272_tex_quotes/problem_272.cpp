#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	string a;
	bool first = true;
	getline(cin, a);
	while (!cin.eof())
	{
		vector<char> output;
		for (unsigned int i = 0; i < a.length(); ++i)
		{
			if (a[i] == '"')
			{
				if (first)
				{
					output.push_back('`');
					output.push_back('`');
					first = false;
				}
				else
				{
					output.push_back('\'');
					output.push_back('\'');
					first = true;
				}
			}
			else
			{
				output.push_back(a[i]);
			}
		}
		for (unsigned int i = 0; i < output.size(); ++i)
		{
			cout << output[i];
		}
		cout << endl;
		getline(cin, a);
	}
	return 0;
}
