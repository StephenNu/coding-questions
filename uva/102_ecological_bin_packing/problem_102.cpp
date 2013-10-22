#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;



struct arrangement
{
	public:
		long moves;
		string placement;
		arrangement(long a, string b) : moves(a), placement(b)
		{
		}
		bool operator<( const arrangement& lhs) const
		{
			if (moves != lhs.moves)
				return moves < lhs.moves;
			else
				return placement < lhs.placement;
		}
};

int main()
{
	long a[3], b[3], c[3];
	// B G C
	cin >> a[0] >> a[1] >> a[2] >> b[0] >> b[1] >> b[2] >> c[0] >> c[1] >> c[2];
	while (!cin.eof())
	{
		vector<arrangement> possible;
		arrangement d(b[0] + c[0] + a[1] + c[1] + a[2] + b[2], "BGC");
		arrangement e(b[0] + c[0] + a[1] + b[1] + a[2] + c[2], "BCG");
		arrangement f(a[0] + c[0] + b[1] + c[1] + a[2] + b[2], "GBC");
		arrangement g(a[0] + c[0] + a[1] + b[1] + b[2] + c[2], "CBG");
		arrangement h(a[0] + b[0] + b[1] + c[1] + a[2] + c[2], "GCB");
		arrangement i(b[0] + a[0] + a[1] + c[1] + c[2] + b[2], "CGB");
		possible.push_back(d);
		possible.push_back(e);
		possible.push_back(f);
		possible.push_back(g);
		possible.push_back(h);
		possible.push_back(i);
		sort(possible.begin(), possible.end());
		cout << possible[0].placement << " " << possible[0].moves << endl;
		cin >> a[0] >> a[1] >> a[2] >> b[0] >> b[1] >> b[2] >> c[0] >> c[1] >> c[2];
	}
	return 0;
}
