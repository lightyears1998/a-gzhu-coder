#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

struct number
{
    int val;
    bool operator < (number oth)
    {
        if (abs(val) != abs(oth.val)) return abs(val) < abs(oth.val);
        else return val < oth.val;
    }
} num[10010];

int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        for (int i = 0; i < n; i++)
            scanf("%d", &num[i].val);
        sort(num, num + n);
        for (int i = 0; i < n; i++)
        {
            if (i) printf(" ");
            printf("%d", num[i].val);
        }
        printf("\n");
    }
}
