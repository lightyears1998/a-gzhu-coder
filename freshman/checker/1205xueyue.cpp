/* GZHUOJ1301 - 挤牛奶 */
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
 
struct farmer
{
    long long b_t;
    long long e_t;
} F[5050];
 
bool mark[5050];
 
bool compare(farmer a, farmer b)
{  
    if (a.b_t != b.b_t) return a.b_t < b.b_t;
    else return a.e_t < b.e_t;
}
 
int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        memset(mark, false, sizeof(mark));
        
        for (int i = 1; i <= n; i++)
        {
            scanf("%lld%lld", &F[i].b_t, &F[i].e_t);            
        }
        
        sort(F+1, F+1+n, compare);
        
        long long max_ct = 0;
        long long max_et = 0;
//!     long long max_et = F[1].b_t;
         
        for (int i = 1; i <= n; i++)
        {
            if (mark[i] == true) continue;
            long long b_t = F[i].b_t;
            long long e_t = F[i].e_t;
            
            for (int t = i; t <= n; t++)
            {
                if (e_t >= F[t].b_t)
                {
                    mark[t] = true;
                    e_t = max(e_t, F[t].e_t);
                }
                else
                {
                    max_ct = max(max_ct, e_t - b_t);
                    max_et = max(max_et, F[t].b_t - e_t);
                    break;
                }

                if (t == n)
                {
                    max_ct = max(max_ct, e_t - b_t);
                    max_et = max(max_et, F[t].b_t - e_t);
                }
            }
        }
        printf("%lld %lld\n", max_ct, max_et);
    } 
}
