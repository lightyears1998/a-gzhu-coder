#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        long long mx = -1, mx2 = -1, vol = 0;

        for (int i = 1; i <= n; i++)
        {
            int tmp; scanf("%d", &tmp);
            vol += tmp;
        }

        for (int i = 1; i <= n; i++)
        {
            long long tmp; scanf("%lld", &tmp);
            if (tmp >= mx) {
                swap(mx, mx2);
                swap(tmp, mx);
            } else if (tmp > mx2) swap(mx2, tmp);
        }

        if (mx + mx2 >= vol) printf("YES\n");
        else printf("NO\n");
    }
}
