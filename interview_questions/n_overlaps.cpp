#include <iostream>

using namespace std;

/*
	Given n number of ranges, return the overlap of all of them,

	input is correct ranges for an array. ie >= 0 (not dealt with in code)
	that if the set is nonempty then all ranges overlap, and not just a few.
	

	no overlap is found I return an imposible range. ie low > high
*/

struct answer {
	unsigned int low;
	unsigned int high;
};

struct answer num_overlaps(unsigned int a[][2], unsigned int n)
{
	struct answer range;
	if (n != 0)
	{
		unsigned int low = 0, high = a[0][1];
		for (unsigned int i = 0; i < n; ++i)
		{
			if (a[i][0] > low)
			{
				low = a[i][0];
			}
			if (a[i][1] < high)
			{
				high = a[i][1];
			}
		}
		if (low > high)
		{
			range.low = 1;
			range.high = 0;
		}
		else
		{
			range.low = low;
			range.high = high;
		}
	}
	else
	{
		range.low = 0;
		range.high = -1;
	}
	return range;
}

int main()
{
	unsigned int a[2][2] = {{0,3},{4,9}};
	struct answer range = num_overlaps(a, 2);
	if (range.low <= range.high )
	{
		cout << range.low << " " << range.high << endl;
	}
	else
	{
		cout << "no overlap exists" << endl;
	}
	return 0;
}	
