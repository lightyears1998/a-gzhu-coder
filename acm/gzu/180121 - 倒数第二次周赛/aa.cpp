#include <bits/stdc++.h>
using namespace std;

vector<long long> num;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif
	
	long long n, mod; 
	while (cin >> n >> mod)
	{
		num.clear();
		
		while (n--)
		{
			long long t; cin >> t;
			num.push_back(t);
		}
		
		if (mod <= 0) {
			cout << "NO" << endl;
			continue;
		}
		
		long long mx = -1;
		for (int i = 0; i < num.size(); ++i)
		{
			for (int j = i + 1; j < num.size(); ++j)
			{
				for (int k = j + 1; k < num.size(); ++k)
				{
					long long sum = num[i] + num[j] + num[k];
					if (sum % mod == 0) mx = max(mx, sum);
				}
			}
		}
		
		if (~mx) cout << mx << endl;
		else cout << "NO" << endl;
	}
}
