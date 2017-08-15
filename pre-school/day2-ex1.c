/**
 * 时间：17-8-14
 *
 * 作者：仙女（学姐）
 *
 * 题目：
 * 求n的阶乘和（原谅我打不出数学符号）：初始条件：n = 1; n <= 20;
 * 具体操作呢就是求 1！+ 2！+ 3！+…… +20！。
 */

#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", &n);

    long long int result=0;
    for(int c=1; c<=n; c++)
    {
        long long int g=1;
        for(int t=1; t<=c; t++)
        {
            g *= t;
        }
        result += g;
    }

    printf("%lld", result);

    return 0;
}
