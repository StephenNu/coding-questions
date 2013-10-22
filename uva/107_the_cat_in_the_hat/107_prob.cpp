#include <iostream>
#include <cstdio>
using namespace::std;

int main()
{
	int height, workers;
	cin >> height >> workers;
	while (height != 0 && workers != 0)
	{
		bool found = false;
		for (long N = 1; !found; ++N)
		{
			long total_height = 0;
			long non_workers = 0;
			long curr_level = 1;
			long curr_height = height;
			while (curr_height > 1)
			{
				total_height += curr_height*curr_level;
				non_workers += curr_level;
				curr_level *= N;
				curr_height = curr_height/(N + 1);
			}
			if (curr_level == workers)
			{
				total_height += workers;
				found = true;
				printf("%ld %ld\n", non_workers, total_height);
			}
		}

		cin >> height >> workers;
	}
	return 0;
}
