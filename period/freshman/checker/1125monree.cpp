/* GZHUOJ1433 - 序列中最大的数 */
#include <cstdio>

const int MAXN = 1000010;

int a[MAXN];
int mx[MAXN];

int main()
{
    // 打表
    a[0] = 0; a[1] = 1; mx[0] = 0;
    for (int i = 1; i < MAXN; i++)
    {
        if (i * 2 < MAXN) a[i * 2] = a[i];
        if (i * 2 + 1 < MAXN) a[i * 2 + 1] = a[i] + a[i + 1];
        (a[i] > mx[i - 1]) ? (mx[i] = a[i]) : (mx[i] = mx[i - 1]);
    }

    int t; scanf("%d", &t);
    while (t--)
    {
        int n; scanf("%d", &n);
        printf("%d\n", mx[n]);
    }
}
