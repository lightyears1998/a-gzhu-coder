#include <bits/stdc++.h>
using namespace std;

const int maxN = 10086;

int ans[maxN], prime[maxN], tot;
bool isprime[maxN];

void seive()
{
	memset(isprime, true, sizeof(isprime));
	isprime[0] = isprime[1] = false;
	
	for (int i=2; i<maxN; ++i) {
		if (isprime[i]) prime[tot++] = i;
		
		for (int j=0; j<tot && i+prime[j] < maxN; ++j) {
			if (i*prime[j] < maxN) isprime[i*prime[j]] = false;
			if (isprime[i] && i != prime[j])
				ans[i+prime[j]]++; 
		}
	}
}

int main()
{
	seive();

	int n; 
	while (scanf("%d", &n) == 1 && n) {
		printf("%d\n", ans[n]);
	}
}
