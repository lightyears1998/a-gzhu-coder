#include <bits/stdc++.h>
using namespace std;

const int maxN = 1000100;

int tot;
int prime[maxN];
bool isprime[maxN];

void seive()
{
	memset(isprime, true, sizeof(isprime));
	isprime[0] = isprime[1] = false;
	
	for (int i=2; i<maxN; ++i) {
		if (isprime[i]) {
			prime[tot++] = i;
		}
		for (int j=0; j<tot && i*prime[j] < maxN; ++j) {
			isprime[i*prime[j]] = false;
			if (i % prime[j] == 0) break;
		}
	}
}

int decompose(int n) {
	int big = 2;
	for (int i=2; i*i<=n; ++i) {
		while (n % i == 0) 
			big = i, n/=i;
	}
	if (n>1) big = n;
	
	int pos = lower_bound(prime, prime+tot, big)-prime;
	return pos+1;
}

int main()
{
	seive();
	
	int n; 
	while (scanf("%d", &n) == 1) {
		if (n == 1) {
			printf("0\n"); continue;
		}
		printf("%d\n", decompose(n));
	}
}
