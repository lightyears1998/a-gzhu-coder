/* P122T8 - 利用重载函数编程序分别把两个数和三个数从大到小排列 */
#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void sort(int a, int b)
{
    if (a > b) cout << a << " " << b << endl;
    else cout << b << " " << a << endl;
}

void sort(int a, int b, int c)
{
    if (a < b) swap(a, b);
    if (a < c) swap(a, c);
    if (b < c) swap(b, c);
    cout << a << " " << b << " " << c << endl;
}

int main()
{
    for (int i = 0; i < 10; i++)
    {
        if (i % 2) sort(rand(), rand(), rand());
        else sort(rand(), rand());
    }
}
