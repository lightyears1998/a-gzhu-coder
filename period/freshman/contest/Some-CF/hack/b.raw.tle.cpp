#include <bits/stdc++.h>
using namespace std;

const int maxN = 10086;

bool isprime[maxN];
int prime[maxN], tot;

void seive()
{
	memset(isprime, true, sizeof(prime));
	isprime[0] = isprime[1] = false;
	
	for (int i=2; i<maxN; ++i) {
		if (isprime[i]) prime[tot++] = i;
		for (int j=0; j<tot && i*prime[j] < maxN; ++j) {
			isprime[i*prime[j]] = false;
			if (i % prime[j] == 0) break;
		}
	}
} 

int main()
{
	seive();
	
	int n; 
	while (scanf("%d", &n) == 1 && n)
	{
		int ans = 0;
		for (int i=0, j=tot-1; i<j; )
		{
			int sum = prime[i] + prime[j];
			if (sum == n) ++ans, ++i, --j;
			if (sum < n) ++i; 
			if (sum > n) --j;
		}
		printf("%d\n", ans);
	}
} 
