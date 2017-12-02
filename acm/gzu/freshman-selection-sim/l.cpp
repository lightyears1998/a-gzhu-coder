#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    int energy[1010];
    while (scanf("%d", &n) == 1)
    {
        for (int i = 0; i < n; i++) scanf("%d", &energy[i]);
        long long mx = 0, tot = 0;
        for (int i = 0; i < n; i++)
        {
            tot += energy[i];
            if (tot < 0) tot = 0;
            mx = max(mx, tot);
        }
        printf("%lld\n", mx);
    }
}
