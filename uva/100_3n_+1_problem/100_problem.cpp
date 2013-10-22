#include <iostream>
	
using namespace::std;

int findLength(long input);

int main(void)
{
int i,j,k,max=0, current;
	while (cin >> i >> k)
	{
	if (i <= k)
	{
	max = findLength(i);
	for (j = i+1; j <= k; j++)
	{
		current = findLength(j);
		if (current > max)
		{
			max = current;
		}
	}
	cout << i << " " << k << " " << max << endl;
	}
	else
	{
	max = findLength(k);
	for (j = k+1; j <= i; j++)
	{
		current = findLength(j);
		if (current > max)
		{
			max = current;
		}
	}
	cout << i << " " << k << " " << max << endl;
	}
	}
	return 0;
}

int findLength(long input)
{
	int counter = 1;
	while (input != 1)
	{
		counter++;
		if (input % 2 == 0)
			input /= 2;
		else
			input = input*3 + 1;
	}
	return counter;
}