#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		int cnt = 0;
		for (int i=2; i*i<=n; ++i)
		{
			while (n % i == 0) {
				printf(cnt ? "*%d" : "%d", i);
				n /= i;
				++cnt;
			}
		}
		if (n > 1)
			printf(cnt ? "*%d" : "%d", n);
		printf("\n");
	}
}
