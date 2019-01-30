#include <bits/stdc++.h>
using namespace std;

long long tgcd[1010][1010];
long long tprefixsum[1010][1010]; 
long long ttotsum[1010];

long long gcd(int a, int b)
{
	if (tgcd[a][b]) return tgcd[a][b];
	else return tgcd[a][b] = b == 0 ? a : gcd(b, a % b);
}

int main()
{
	for (int i = 1; i < 1010; ++i)
	{
		for (int j = 1; j < 1010; ++j)
		{
			tprefixsum[i][j] += tprefixsum[i][j - 1] + gcd(i, j);
		}
	}
	for (int i = 1; i < 1010; ++i)
	{
		for (int j = 1; j <= i; ++j)
		{
			ttotsum[i] += tprefixsum[j][i];
		}
	}
	
	int n; 
	while (scanf("%d", &n) == 1)
	{
		printf("%lld\n", ttotsum[n]);
	}
}
