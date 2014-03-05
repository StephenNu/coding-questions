#include <iostream>
#include <vector>
using namespace std;

bool inside(int lines, int cols, int c, int r)
{
	if ((r >= 0 && r < lines) && (c >= 0 && c < cols))
		return true;
	else
		return false;
}
char increase(vector<string> a, int i, int j)
{
	if (a[j].at(i) == '*')
		return '*';
	else if (a[j].at(i) == '.')
		return '1';
	else
		return ++a[j].at(i);
}

int main()
{
	int lines, m;
	int t = 1;
	string curr;
	vector<string> a;
	cin >> lines >> m;
	while (lines &&  m)
	{
		if (t > 1)
			cout << endl;
		a.clear();
		for (int i = 0; i < lines; ++i)
		{
			cin >> curr;
			a.push_back(curr);
		}
		for (int j = 0; j < lines; ++j)
		{
			for (int k = 0; k < m; ++k)
			{
				if (a[j].at(k) == '*')
				{
					if (inside(lines, m, k-1, j-1))
					{
						a[j-1].at(k-1) = increase(a, k-1, j-1);
					}
					if (inside(lines, m, k-1, j))
					{
						a[j].at(k-1) = increase(a, k-1, j);
					}
					if (inside(lines, m, k-1, j+1))
					{
						a[j+1].at(k-1) = increase(a, k-1, j+1);
					}
					if (inside(lines, m, k, j-1))
					{
						a[j-1].at(k) = increase(a, k, j-1);
					}
					if (inside(lines, m, k, j+1))
					{
						a[j+1].at(k) = increase(a, k, j+1);
					}
					if (inside(lines, m, k+1, j+1))
					{
						a[j+1].at(k+1) = increase(a, k+1, j+1);
					}
					if (inside(lines, m, k+1, j))
					{
						a[j].at(k+1) = increase(a, k+1, j);
					}
					if (inside(lines, m, k+1, j-1))
					{
						a[j-1].at(k+1) = increase(a, k+1, j-1);
					}
				}
				else if (a[j].at(k) == '.')
				{
					a[j].at(k) = '0';
				}
			}
		}
		cout << "Field #" << t++ << ":" <<  endl;
		for (unsigned int q = 0; q < a.size(); ++q)
		{
			cout << a[q] << endl;
		}
		cin >> lines >> m;
	}
	return 0;
}
