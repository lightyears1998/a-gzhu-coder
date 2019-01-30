#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{	
		long long ans = 0, cur, prev = 0, com;
		for (int i = 0; i <= n; ++i)
		{
			if (i != n) scanf("%lld", &cur); else cur = 0;
			com = min(cur, prev), prev -= com, cur -= com;
			ans += prev, prev = cur;
		}
		
		printf("%lld\n", ans);
	}
}
