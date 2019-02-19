#include <bits/stdc++.h>
using namespace std;

vector<int> tap;
int cost[220];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif
	
	int t; cin >> t;
	while (t--)
	{
		tap.clear();
		
		int n, k; cin >> n >> k;
		while (k--)
		{
			int t; cin >> t;
			tap.push_back(t);
		}
		for (int i = 1; i <=n; ++i)
		{
			int d = 999;
			for (int c : tap) {
				d = min(d, abs(c-i)+1);
			}
			cost[i] = d;
		}
		
		cout << *max_element(cost+1, cost+1+n) << endl;
	}
}

