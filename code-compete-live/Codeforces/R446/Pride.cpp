/**
 * 对于一个含有n个元素的数列：
 * 1）若存在k个1，则需要(n - k)步来达成要求
 * 2）若不存在1，则需要贪心求出得到一个1需要的最短步数。
**/
#include <iostream>
#include <cmath>
using namespace std;

int num[2010];

int gcd(int a, int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

int main()
{
    int n; cin >> n;

    int cnt1 = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
        if (num[i] == 1) cnt1++;
    }

    if (cnt1) {
        cout << n - cnt1 << endl;
        return 0;
    }

    int mn = n + 1; // 达成要求需要的最短步数
    for (int i = 0; i < n; i++)
    {
        int cur = num[i];
        for (int j = i; j < n; j++)
        {
            cur = gcd(cur, num[j]);
            if (cur == 1) {
                mn = min(mn, abs(i - j));
                break;
            }
        }
    }

    if (mn == n + 1) cout << -1 << endl;
    else cout << n - 1 + mn << endl;
}

/* 超时 - 只需稍微的改进就能大大增强算法的效率 */
// int mn = n + 1; // 达成要求需要的最短步数
// for (int i = 0; i < n; i++)
// {
//     for (int j = i; j < n; j++)
//     {
//         int idle = num[i];
//         for (int k = i + 1; k <= j; k++) idle = gcd(idle, num[k]);
//         if (idle == 1) {
//             mn = min(mn, abs(i - j));
//         }
//     }
// }

/* 错误的想法 */
//! if (gcd(num[i], num[j]) == 1) {
//      mn = min(mn, abs(i - j));
//! }
