#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n; cin >> n;
	int ans = 0;
	
	for (int i = 1; i <= n; ++i)
	{
		for (int j = i; j <= n; ++j)
		{
			int k = i ^ j;
			if (k >= j && k <= n && i + j > k) {
				++ans;
			}
		}
	} 
	cout << ans << endl; 
}

