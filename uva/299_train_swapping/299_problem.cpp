#include <iostream>
#include <vector>

using namespace std;

void swap(int* a, int* b)
{
	int c = *a;
	*a = *b;
	*b = c;
}
int find(unsigned int a, vector<unsigned int>& b)
{
	for (unsigned int i = 0; i < b.size(); ++i)
	{
		if (b[i] == a)
		{
			return i;
		}
	}
	return -1;
}
int main()
{
	vector<unsigned int> a;
	unsigned int t, l, b, current, swaps;
	cin >> t;
	for (unsigned int i = 0; i < t; ++i)
	{
		a.clear();
		swaps = 0;
		cin >> l;
		for (unsigned int j = 0; j < l; ++j)
		{
			cin >> b;
			a.push_back(b);
		}
		for (current = 1; current <= l; ++current)
		{
			int index = find(current, a);
			for (unsigned int q = index; q+1 > current; q--)
			{
				swap(a[q], a[q-1]);
				swaps++;
			}
		}
		cout << "Optimal train swapping takes " << swaps << " swaps." << endl;
	}
	return 0;
}
