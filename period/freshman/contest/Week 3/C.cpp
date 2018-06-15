#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int maxN = 1010;
const LL INF = 0x3F3F3F3F3F3F3F3F;

LL num[maxN], sum[maxN];

int main()
{
	int n; 
	while (scanf("%d", &n) == 1 && n) 
	{
		memset(num, 0, sizeof(num));
		memset(sum, 0, sizeof(sum));
		
		num[0] = -INF;
		for (int i=1; i<=n; ++i) {
			scanf("%lld", &num[i]); 
		}
		
		for (int i=1; i<=n; ++i) {
			int amx = 0;
			for (int j=0; j<i; ++j)	{
				if (num[j] < num[i] && sum[j]>amx) {
					amx = sum[j];
				}
			}
			sum[i] = num[i] + amx;
		} 
		
		printf("%lld\n", *max_element(sum, sum+1+n));
	}
}
