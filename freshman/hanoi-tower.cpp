/* 暴力求解汉诺塔问题 */
#include <iostream>
using namespace std;

unsigned long long scheme[70] = {0, 1};

unsigned long long move(int num)
{
    if (scheme[num]) return scheme[num];
    else scheme[num] = move(num - 1) + 1 + move(num - 1);
    return scheme[num];
}

int main()
{
    int n;
    while (cin >> n)
    {
        cout << move(n) << endl;
    }
}
