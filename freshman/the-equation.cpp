/**
 * @不怼、:
 *
 *        B   DEF
 *    A + — + ——— = 10
 *        C   GHI
 * 这个算式中A~I代表1~9的数字，不同的字母代表不同的数字。
 * 比如：
 * 6+8/3+952/714=10就是一种解法，
 * 5+3/1+972/486=10是另一种解法。
 * 这个算式一共有多少种解法？
 *
**/
#include <iostream>
#include <cmath>
#define rep(i, n, m) for (int i = int(n); i < m; ++i)
#define unq(a, b) if (a == b) continue

const double EPS = 1e-8;

int main()
{
    int cnt = 0;

    rep(a, 1, 10) rep(b, 1, 10) rep(c, 1, 10)
    rep(d, 1, 10) rep(e, 1, 10) rep(f, 1, 10)
    rep(g, 1, 10) rep(h, 1, 10) rep(i, 1, 10)
    {
        unq(a, b); unq(b, c); unq(c, d); unq(d, e); unq(e, f); unq(f, g); unq(g, h); unq(h, i); 
        unq(a, c); unq(b, d); unq(c, e); unq(d, f); unq(e, g); unq(f, h); unq(g, i);
        unq(a, d); unq(b, e); unq(c, f); unq(d, g); unq(e, h); unq(f, i);
        unq(a, e); unq(b, f); unq(c, g); unq(d, h); unq(e, i);
        unq(a, f); unq(b, g); unq(c, h); unq(d, i);
        unq(a, g); unq(b, h); unq(c, i);
        unq(a, h); unq(b, i);
        unq(a, i);

        double rslt = a + (double)b / c + (double)(d * 100 + e * 10 + f) / (g * 100 + h * 10 + i);
        if (fabs(rslt - 10) < EPS)
        {
            printf("%d + %d/%d + %d%d%d/%d%d%d = 10\n", a, b, c, d, e, f, g, h, i);
            cnt++;
        }
    }
    printf("Total: %d\n", cnt);
}
