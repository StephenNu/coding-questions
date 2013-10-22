#include <iostream>
#include <vector>

using namespace std;

struct farmer
{
	int farmyard;
	int num_animals;
	int environ;
	double premium;
	farmer(int y, int n, int e, double p) : farmyard(y), num_animals(n), environ(e), premium(p)
	{
	}
};

int main()
{
	int test_cases;
	cin >> test_cases;
	for (int k = 0; k < test_cases; ++k)
	{
		int num_farm;
		double yard, animals, environment;
		double total = 0;
		vector<farmer> a;
		cin >> num_farm;
		for (int i = 0; i < num_farm; ++i)
		{
			cin >> yard >> animals >> environment;
			farmer f(yard, animals, environment, ((yard/animals)*environment*animals) );
			a.push_back(f);
		}
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			total += a[i].premium;
		}
		cout << total << endl;
	}
	return 0;
}
