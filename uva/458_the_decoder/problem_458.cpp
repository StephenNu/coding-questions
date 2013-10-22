#include <iostream>
#include <string>
using namespace std;
int main()
{
	string a;
	getline(cin, a);
	while (!cin.eof())
	{
		for (unsigned int i = 0; i < a.length(); ++i)
		{
			a[i] -= 7;
		}
		cout << a << endl;
		getline(cin, a);
	}
	return 0;
}
