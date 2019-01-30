#include <bits/stdc++.h>
using namespace std;
  
long long val[1001000];
bool mark[1001000];
  
int main()
{
    int n; long long mod;
    while (scanf("%d%lld", &n, &mod) == 2)
    {
        memset(mark, 0, sizeof(mark));
          
        bool ok = false;
        for (int i = 0; i < n; ++i)
        {
            scanf("%lld", &val[i]);
            if (i) val[i] += val[i-1];
            val[i] %= mod;
              
            if (mark[val[i]] || val[i] == 0) ok = true;
            mark[val[i]] = true;
        }
          
        puts(ok ? "Yes" : "No");
    }
}
