/* 白色相簿的季节 */
#include <cmath>
#include <iostream>
using namespace std;

long long rslt[20];

int main()
{
    long long factorial = 1;
    for (int i = 1; i < 20; i++)
    {
        factorial *= i;
        rslt[i] = floor(factorial / exp(1) + 0.5);
    }

    int n;
    while (cin >> n)
    {
        cout << rslt[n] << endl;
    }
}
