#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	vector<long long> a;
	for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			for (int k = 0; k < 12; ++k)
			{
				long long b= pow(2,k)*pow(3,j)*pow(5,i);
				a.push_back(b);
			}
		}
	}
	sort(a.begin(), a.end());
	unique(a.begin(), a.end());
	// 576650390625
	cout << a[0] << " " << a[1499] << endl;
	return 0;
}
