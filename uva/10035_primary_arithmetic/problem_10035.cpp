#include <iostream>

using namespace std;

int main()
{
	unsigned int a, b;
	cin >> a >> b;
	while (a != 0 || b != 0)
	{
		long num_carries = 0;
		int prev_carr = 0;
		while (a != 0 || b != 0)
		{
			prev_carr = (a%10 + b%10 + prev_carr)/10;
			if (prev_carr)
			{
				++num_carries;
			}
			a /= 10;
			b /= 10;
		}
		if (num_carries == 0)
		{
			cout << "No carry operation." << endl;
		}
		else if (num_carries == 1)
		{
			cout << num_carries << " carry operation." << endl;
		}
		else
		{
			cout << num_carries << " carry operations." << endl;
		}
		cin >> a >> b;
	}
	return 0;
}
