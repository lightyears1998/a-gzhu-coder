#include <iostream>
#include <climits>
using namespace std;

int main()
{
    long double n, m, p;
    while (cin >> n >> m >> p)
    {
        // 利用组合数学公式简化运算
        long double s1 = (1 + n) * n / 2;
        long double s2 = n * (n + 1) * (2 * n + 1) / 6;
        long double s3 = 0;
        cout << (s1 + s2) / s3 << endl;
    }
}
