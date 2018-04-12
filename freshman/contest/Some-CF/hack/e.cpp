#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t; scanf("%d", &t);
	while (t--)
	{
		int n, m; scanf("%d%d", &m, &n);
		
		int fine = 0; bool flag = true;
		for (int i=1; i<=n; ++i) {
			int child; scanf("%d", &child);
			if (flag && i > m) {
				fine = (1<<(n-(i-1)))-1;
				flag = false;
			}
			if (flag && child == 1) {
				fine = (1<<(n-i))-1;
				flag = false;
			}
		}
		printf((fine ? "%d0000 RMB\n" : "%d RMB\n"), fine);
	}
}
