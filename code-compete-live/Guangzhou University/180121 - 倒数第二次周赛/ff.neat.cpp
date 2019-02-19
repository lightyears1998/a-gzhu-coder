#include <bits/stdc++.h>
using namespace std;   
int main()
{
	int n; while (~scanf("%d", &n)) 
	{
		long long cur, pre = 0, tot = 0, sub;
		while (n--)
			scanf("%lld", &cur); 
			sub = min(pre, cur);
			pre = cur - sub;
			tot += pre - sub;
		}
		printf("%lld\n", tot);
	}
}

