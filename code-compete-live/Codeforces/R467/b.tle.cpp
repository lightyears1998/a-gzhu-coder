#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL p, y;

bool judge(LL i)
{
	bool flag = true;
	for (LL j = 2; flag && j <= p; ++j)
	{
		if (i % j == 0) flag = false;
	}
	return flag;
}

int main()
{
	cin >> p >> y;
	
	#ifdef LOCAL
	double s = clock();
	#endif
	
	if (p == 2) {
		if (y > 3) cout << (y%2 ? y : y-1) << endl;
		else cout << -1 << endl;
		return 0;
	}
	
	LL ans = 1;
	for (LL i = p+1; i <= y; ++i)
	{
		if (ans*i > y || ans*i < 0) break;
		if (judge(i)) ans *= i;
	}
	cout << ans << endl;
	
	while (ans*(p+1)>0 && ans*(p+1)<= y) ans *= p+1;
	for (LL i = ans+1; i <= y; ++i) if (judge(i)) ans = i;
	
	#ifdef LOCAL
	cout << (clock() - s) / CLOCKS_PER_SEC << endl;
	#endif
	
	if (ans == 1) cout << -1 << endl;
	else cout << ans << endl;
}
