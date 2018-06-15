/* Unsolved */
#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <cstring>
using namespace std;

const int  nf = 0x3F3F3F3F;

int s, t, n, m;
int lu[10010][10010];
int dp[10010];
bool mr[10010];

int main()
{
	while (scanf("%d%d", &n, &m) == 2)
	{
		if (n == 0 && m == 0) return 0;

		memset(lu,0, sizeof(lu));
		memset(dp, 0, sizeof(dp));
		memset(mr, false, sizeof(mr));

		for (int i = 0; i < n; i++) lu[i][i] = 0;
		for (int i = 0; i < m; i++)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			lu[a][b] = max(lu[a][b], c);
			lu[b][a] = lu[a][b];
		}
		s = 0; t = n - 1; dp[s] = 0;
		for (int i = 0; i < n && !mr[t]; i++)
		{
			int amin = -1;
			int mpr = s;
			for (int j = 0; j < n; j++) if (!mr[j] && dp[j] > amin)
			{
				 amin = dp[j]; mpr = j;
			}
			for (int j = 0; j < n; j++)
			{
				if (mr[mpr]) continue; dp[j] = max(dp[j], dp[mpr] + lu[mpr][j]);
			}
			mr[mpr] = 1;
		}
		printf("%d\n", dp[t]);
	}
}
