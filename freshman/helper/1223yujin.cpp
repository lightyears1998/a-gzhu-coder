/**
 * 斐波那契数列当n很大时如何高效的求借第n项a(n) mod M的值? - 王希的回答 - 知乎
 * https://www.zhihu.com/question/23582123/answer/40464211
**/
#include <cstdio>
#include <cstring>
using namespace std;

const int mod = 66666;

struct matrix
{
    int val[2][2];
    matrix operator *(matrix m)
    {
        matrix tmp; memset(&tmp, 0, sizeof(tmp));
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    tmp.val[i][j] += val[i][k] * m.val[k][j];
                    tmp.val[i][j] %= mod;
                }
            }
        }
        return tmp;
    }
    matrix operator *=(matrix b)
    {
        *this = *this * b;
    }
};

// 定义矩阵常数
const matrix basic =
{
    {1, 1, 1, 0}
};

// 求矩阵a的n次幂
matrix qpow(matrix a, int n)
{
    matrix ans = {{1, 0, 0, 1}}, base = basic;
    while (n)
    {
        if (n & 1) ans *= base;
        base *= base;
        n >>= 1;
    }
    return ans;
}

int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        matrix vec = qpow(basic, n);
        int ans = (vec.val[1][0] + vec.val[1][1]) % mod;
        printf("%d\n", ans);
    }
}
