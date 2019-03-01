/*
* this code is made by lightyears
* Problem: 1514
* Verdict: Accepted
* Submission Date: 2018-04-10 13:44:22
* Time: 8 MS
* Memory: 2020 KB
*/
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
 
int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif
     
    int t; scanf("%d", &t);
    while (t--) {
        LL k, p; scanf("%lld%lld", &k, &p);
         
        LL mx = 0, mn = 0, ths = p;
        while (ths) {
            if (ths && ths!=1) ++mx;
            ths >>= 1;
        }
        if (p==(1LL<<k)) {
            mn = mx;
        }
         
        printf("%lld %lld\n", mx, mn);
    }
}