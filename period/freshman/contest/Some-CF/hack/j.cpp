#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main()
{
	LL n;
	while (scanf("%lld", &n) == 1)
	{
		n %= 10000;
		LL ans = n*n*(n+1)*(n+1)/4;
		printf("%04lld\n", ans%10000);
	}
}
