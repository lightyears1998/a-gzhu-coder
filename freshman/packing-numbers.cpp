/* 将四个范围在0~255之间的整数压缩到一个unsigned int里 */
#include <iostream>
#include <cstdio>
using namespace std;

unsigned pack(int, int, int, int);
void unpack(unsigned, int&, int&, int&, int&);

int main()
{
    int a, b, c, d;
    while (cin >> a >> b >> c >> d)
    {
        int i, j, k, m;
        unsigned packed = pack(a, b, c, d);
        unpack(packed, i, j, k, m);
        printf("Packed: %u Origin: %d %d %d %d\n", packed, i, j, k, m);
    }
}

// 将a, b, c, d四个整数的低8位压缩到一个unsigned int中
unsigned pack(int a, int b, int c, int d)
{
    int mask = 0xFF; unsigned rslt = 0;
    rslt += a & mask;
    rslt += (b & mask) << 8;
    rslt += (c & mask) << 16;
    rslt += (d & mask) << 24;
    return rslt;
}

// 从一个unsigned int中提取a, b, c, d
void unpack(unsigned packed, int &a, int &b, int &c, int &d)
{
    int mask = 0xFF;
    a = packed & mask;
    b = (packed >> 8) & mask;
    c = (packed >> 16) & mask;
    d = (packed >> 24) & mask;
}
