/* P122T2 - 使用程序计算数学表达式的值，注意判断溢出的情况 */
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    long long m, n, p;
    while (cout << "n, m, p: ", cin >> n >> m >> p)
    {
        // 利用组合数学公式简化运算
        long long s1 = (1 + n) * n / 2;
        long long s2 = m * m * (m + 1) * (m + 1) / 4;
        long long s3 = p * p * (p + 1) * (p + 1) * (2 * p * p + 2 * p - 1) / 12;
        // 判断溢出
        if (s1 < 0 || s2 < 0 || s3 < 0) // 不能检测出所有溢出情况
        {
            cout << "Overflow!" << endl;
            continue;
        }
        cout << "Result: " << (double)(s1 + s2) / s3 << endl;
    }
}
