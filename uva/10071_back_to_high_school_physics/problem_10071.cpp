#include <iostream>
using namespace std;
int main()
{
	double v, t;
	cin >> v >> t;
	while (!cin.eof()) 
	{
		if (t == 0)
		{
			cout << 0 << endl;
		}
		else
		{
			cout <<  0.5*(v/t)*((2*t)*(2*t)) << endl;
		}
		cin >> v >> t;
	}
	return 0;
}
