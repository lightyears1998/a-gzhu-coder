/*
* this code is made by lightyears
* Problem: 1523
* Verdict: Accepted
* Submission Date: 2018-04-10 15:13:02
* Time: 20 MS
* Memory: 25692 KB
*/
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
 
const int maxN = 1010100;
 
int n, m;
LL v[maxN], g[maxN]; int tot;
LL dp[maxN];
 
int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif
     
    int t; scanf("%d", &t);
    while (t--) {
        tot = 0;
         
        scanf("%d%d", &n, &m);
        for (int i=0; i<n; ++i)
        {
            int vi, gi, ai; scanf("%d%d%d", &vi, &gi, &ai);
             
            int base = 1;
            while (ai >= base) {
                v[tot]=vi*base, g[tot]=gi*base, ai-=base;
                ++tot; base <<= 1;
            }
            if (ai) {
                v[tot]=vi*ai, g[tot]=gi*ai, ++tot;
            }
        }
         
        memset(dp, 0, sizeof(dp));
        for (int i=0; i<tot; ++i) {
            for (int j=m; j>=g[i]; --j) {
                dp[j] = max(dp[j], dp[j-g[i]]+v[i]);
            }
        }
 
        LL mx = *max_element(dp, dp+m+1);
        printf("%lld\n", mx);
    }
}