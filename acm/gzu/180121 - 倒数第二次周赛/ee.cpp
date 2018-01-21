#include <bits/stdc++.h>
using namespace std;

const int mx = 1001000;

long long num[mx];

int lowbit(int i)
{
	return i&(-i);
}

long long add(int x, int v)
{
	for (int i = x; i < mx; i += lowbit(i))
	{
		num[i] += v;
	}
}

long long gets(int x)
{
	long long rslt = 0;
	for (int i = x; i; i -= lowbit(i)) rslt += num[i];
	return rslt;
}


int main()
{
	int n, mod;
	while (scanf("%d%d", &n, &mod) == 2)
	{
		memset(num, 0, sizeof(num));
		
		for (int i = 1; i <= n; ++i)
		{
			int t; scanf("%d", &t);
			add(i, t);
		}
		
		bool ok = false;
		for (int tt = 1; !ok && tt <= n; ++tt)
		{
			for (int i = 1; i + tt - 1 <= n; ++i)
			{
				long long cur = gets(i + tt - 1) - gets(i - 1);
				if (cur % mod == 0) ok = true;
			}
		}
		
		printf(ok ? "Yes\n" : "No\n");
	}
}
