/* 暴力求解汉诺塔问题 */
#include <iostream>
#include <cstdio>
using namespace std;

unsigned long long scheme[70] = {0, 1};

unsigned long long move(int num)
{
    if (scheme[num]) return scheme[num];
    else scheme[num] = move(num - 1) + 1 + move(num - 1);
    return scheme[num];
}

// 经典模式/演示模式：无优化
// unsigned long long move(int num)
// {
//     if (num == 1) return 1;
//     else {
//         printf("Want to know move(%d)\tCalculating move(%d - 1)\n", num, num);
//         printf("Get move(%d - 1) = %lld\n", num, move(num - 1));
//         return move(num - 1) + 1 + move(num - 1);
//     }
// }

int main()
{
    int n;
    while (cin >> n)
    {
        cout << move(n) << endl;
    }
}
