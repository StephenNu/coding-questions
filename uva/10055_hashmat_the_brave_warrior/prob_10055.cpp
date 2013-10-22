#include <iostream>

using namespace::std;

int main(void)
{
	long long j, i;
	// Read numbers until EOF
	while (cin >> j >> i)
	{
		if (j < i)
		{
			cout << i-j << endl;
		}
		else
		{
			cout << j-i << endl;
		}
	}
	return 0;
}
