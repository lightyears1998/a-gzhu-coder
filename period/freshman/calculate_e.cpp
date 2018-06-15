/* 计算自然对数的底数e */
#include <iostream>
using namespace std;

long double cal_e(long long seed);
long double get_e(long double eps);

int main()
{
    cout.flags(cout.fixed);
    cout.precision(18);
    cout << get_e(1e-10) << endl;
}

long double cal_e(long long seed)
{
    long double rslt = 1;
    long double cell = 1 + 1 / (long double)seed;
    for (int n = 1; n <= seed; n++)
    {
        rslt *= cell;
    }
    return rslt;
}

long double get_e(long double eps)
{
    long double val = 0, lst;
    long long seed = 1;
    do
    {
        lst = val;
        val = cal_e(seed++);
        if (!(seed % 10000)) cout << val << endl;
    } while (val - lst > eps);
    return val;
}
