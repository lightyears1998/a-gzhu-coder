/*
* this code is made by lightyears
* Problem: 1513
* Verdict: Accepted
* Submission Date: 2018-04-10 13:27:35
* Time: 0 MS
* Memory: 2020 KB
*/
#include <bits/stdc++.h>
using namespace std;
 
const int maxN = 1010;
 
int n, m;
bool alive[maxN];
 
int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif
     
    int t; scanf("%d", &t);
    while (t--)
    {  
        memset(alive, true, sizeof(alive));
         
        scanf("%d%d", &n, &m);
        for (int i=0; i<m; ++i) {
            int cur; scanf("%d", &cur);
            if (cur) alive[cur] = false;
        }
         
        int can = 0; bool mult = false;
        for (int i=1; i<=n; ++i) {
            if (alive[i]) {
                if (!can) {
                    can = i;
                }
                else mult = true;
            }
        }
         
        if (mult || !can)
            puts("No");
        else puts("Yes");
    }
}