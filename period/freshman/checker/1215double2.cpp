#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int dp[5005];
const int INF = -1e9;

int main()
{
	int a[4];
	int n;
	while (scanf("%d%d%d%d", &n, &a[0], &a[1], &a[2]) != EOF)
	{
		for (int i = 0; i < 5005; i++) dp[i] = INF;
		dp[0] = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = a[i]; j <= n; j++)
			{
				if (dp[j - a[i]] != INF)
					dp[j] = max(dp[j], dp[j - a[i]] + 1);
			}
		}
		printf("%d\n", dp[n]);
	}
	return 0;
}
