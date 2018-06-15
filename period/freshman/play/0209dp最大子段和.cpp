#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main()
{
	int n; cin >> n;
	LL mx = 0, cur = 0;
	while (n--)
	{
		LL nxt; cin >> nxt;
		cur = max(cur + nxt, 0LL);
		mx  = max(mx, cur);
	}
	cout << mx << endl;
}

