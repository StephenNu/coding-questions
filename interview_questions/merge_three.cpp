#include <iostream>
#include <vector>
/*
	merge three arrays that are already in sorted order.
*/
template <class T>
std::vector<T> merge_two(std::vector<T> a, std::vector<T> b)
{
	unsigned int j = 0;
	unsigned int i = 0;
	std::vector<T> fin;
	while ( i < a.size() || j <  b.size())
	{
		if (i < a.size() && a[i] < b[j])
		{
			fin.push_back(a[i++]);
		}
		else if (j < b.size())
		{
			fin.push_back(b[j++]);
		}
		else
		{
			fin.push_back(a[i++]);
		}
	}
	return fin;
}

template <class T>
std::vector<T> merge_three(std::vector<T> a, std::vector<T> b, std::vector<T> c)
{
	return merge_two<T>(a, merge_two<T>(b, c));
}

int main()
{
	std::vector<int> a = {1,3,5,6,9};
	std::vector<int> b = {3,5,6,8};
	std::vector<int> c = {6,8,11,14};
	std::vector<int> result = merge_three<int>(a, b,c);
	for (unsigned int i = 0; i < result.size(); ++i)
	{
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
