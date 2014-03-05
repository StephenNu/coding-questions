#include <iostream>
#include <vector>
using namespace std;

long long reverse(long long a)
{	
	long long result = 0;
	while (a > 0)
	{
		result *= 10;
		result += a%10;
		a /= 10;
	}
	return result;
}

bool isPalin(long long a)
{
	vector<char> b;
	while (a > 0)
	{
		b.push_back(a%10);
		a /= 10;
	}
	for (unsigned int i = 0; i < b.size()/2; ++i)
	{
		if (b[i] != b[b.size()-i-1])
		{
			return false;
		}
	}
	return true;
}


int main()
{
	unsigned int t;
	long long n;
	int additions;
	cin >> t;
	for (unsigned int i = 0; i < t; ++i)
	{
		additions = 0;
		cin >> n;
		while (!isPalin(n))
		{
			n += reverse(n);
			++additions;
		}
		cout << additions << " " << n << endl;
	}
	return 0;
}
