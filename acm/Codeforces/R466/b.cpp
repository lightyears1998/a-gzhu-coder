#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main()
{
	LL n, k, a, b; cin >> n >> k >> a >> b;
	
	LL x = n, cost = 0;
	if (k == 1) 
	{
		cout << a*(n-1) << endl;
		return 0;
	}
	
	while (x != 1)
	{
		if (x % k == 0)
		{
			LL bf = x, af = x/k;
			if (b < (bf-af)*a) {
				x = af; cost += b;
			}
			else {
				x = af; cost += (bf-af)*a;
			}
		}
		else
		{
			LL base = x/k*k; 
			if (base < 1) {
				cost += a*(x-1);
				x = 1;
			}
			else {
				cost += a*(x-base);
				x = base;
			}
		}
	}
	cout << cost << endl;
}
