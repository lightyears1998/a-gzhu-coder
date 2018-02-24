#include <bits/stdc++.h>
using namespace std;

vector<int> num;

int main()
{
	int n, d; cin >> n >> d;
	while (n--)
	{
		int i; cin >> i;
		num.push_back(i);
	}
	
	int mx = 0;
	for (double i = 2; i <= 200; ++i)
	{
		int cur = 0;
		for (unsigned j = 0; j < num.size(); ++j)
		{
			if (abs(i/2 - num[j]) <= (double)d/2) ++cur;
		}
		mx = max(mx, cur);
	}
	
	cout << num.size() - mx << endl;
}
