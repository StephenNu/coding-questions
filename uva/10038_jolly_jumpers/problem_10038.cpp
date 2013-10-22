#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main()
{
	int first, info, check;
	cin >> first;
	while (!cin.eof())
	{
		bool jolly = true;
		vector<int> a, b;
		for (int i = 0; i < first; ++i)
		{
			cin >> info;
			b.push_back(info);
		}
		if (first != 1)
		{
			for (unsigned int i = 0; i < b.size()-1; ++i)
			{
				a.push_back(abs(b[i] - b[i+1]));
			}
			sort(a.begin(), a.end());
			check = 1;
			for (unsigned int i = 1; i < a.size(); ++i)
			{
				if (check+1 != a[i])
				{
					jolly = false;
					break;
				}
				++check;
			}
		}
		else if (info != 1)
		{
			jolly = false;
		}
		if (jolly)
		{
			cout << "Jolly" << endl;
		}
		else
		{
			cout << "Not jolly" << endl;
		}
		cin >> first;
	}
	return 0;
}
