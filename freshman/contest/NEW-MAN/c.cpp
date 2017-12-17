/*
* this code is made by 1706300001
* Problem: 1458
* Verdict: Accepted
* Submission Date: 2017-12-10 13:48:22
* Time: 0 MS
* Memory: 2020 KB
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

bool leap[700];
const int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void init()
{
    for (int i = 0; i < 700; i++)
    {
        if (i % 4 == 0) leap[i] = true;
    }
    leap[100] = false;
    leap[200] = false;
    leap[300] = false;
    leap[500] = false;
    leap[600] = false;

    // for (int i = 0; i < 700; i++) if (leap[i]) cout << 2000 + i << endl;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    init();

    int a, b, c;
    while (scanf("%d%d%d", &a, &b, &c) == 3)
    {
        long long diff = 0;
        for (int i = a - 2000 - 1; i >= 0; i--)
        {
            if (leap[i]) diff += 366;
            else diff += 365;
        }

        for (int i = b - 1; i >= 1; i--)
        {
            diff += month[i];
            if (i == 2) if(leap[a - 2000]) diff++;
        }

        diff += c;

        printf("%lld\n", (4 + diff % 7) % 7 + 1);
    }
}
