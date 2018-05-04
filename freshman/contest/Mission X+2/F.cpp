#include <bits/stdc++.h>
using namespace std;

#define sfi(n) scanf("%d", &n) 

int main()
{
	int t; sfi(t);
	while (t--) {
		int ans = 0;
		
		int n; sfi(n); ans += n;
		while (n--) {
			int cur; sfi(cur);
			ans += cur;
		}
		printf("%d\n", ans);
	}
}
