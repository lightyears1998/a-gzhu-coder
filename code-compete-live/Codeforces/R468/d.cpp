#include <bits/stdc++.h>
using namespace std;

int fa[100100];
int dis[100100], cnt[100100];

int distances(int i)
{
	int cnt = 0;
	while (i != 1 && dis[i] == 0) {
		++cnt, i = fa[i];
	}
	return cnt + dis[i];
}

int main()
{
	int n; scanf("%d", &n);
	
	fa[1] = 1; dis[1] = 0;
	for (int i = 2; i <= n; ++i)
		scanf("%d", &fa[i]);
	
	for (int i = 1; i <= n; ++i) {
		dis[i] = distances(i);
		++cnt[dis[i]];
	}
	
	int ans = 0;
	for (int i = 0; i <= n; ++i)
		ans += cnt[i]%2;
	printf("%d\n", ans);
} 
