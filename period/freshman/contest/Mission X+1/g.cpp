#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
	return b==0 ? a : gcd(b, a%b);
}

int main()
{	
	int T; scanf("%d", &T);
	while (T--) {
		int n, cur; scanf("%d%d", &n, &cur);
		int g = cur;
		for (int i=1; i<n; ++i) {
			scanf("%d", &cur);
			g = gcd(g, cur);
		}
		
		if (g == 1) puts("YES");
		else puts("NO");
	}
}
