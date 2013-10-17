#include <iostream>
#include <queue>
/*
	Given an array, and the size of the array, starting from index find the fewest number of steps to outside the array only eve going the number of 
	steps at each location. i.e a[] = {3, 2, 19, 4 ,1, 2, 1, 1, 3 } would return 2 because starting at 3 we could go to [1], [2], [3] but [2] = 19 
	which would take us out of the array.
	
	assumptions: the values pased are ints, no zero steps, even more so at start ie it is possible to get through the array.
*/
int quickest_steps(int a[], int max)
{
	int steps = 0;
	int current = 0;
	std::priority_queue<int> hash;
	hash.push(a[current++]);
	while (!hash.empty())
	{
		++steps;
		int node = hash.top();
		int leapable = current + node;
		if (leapable >= max)
			return steps;
		else
		{
			hash.pop();
			for (; current < leapable; ++current)
			{
				hash.push(a[current]);
			}
		}
	}
}


int main()
{
	int a[] = {3, 2, 19, 4, 1, 2, 1, 1, 3};
	int steps = quickest_steps(a, 9);
	std::cout << steps << std::endl;
	return 0;
}
