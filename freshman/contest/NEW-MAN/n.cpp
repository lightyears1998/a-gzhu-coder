/*
* this code is made by 1706300001
* Problem: 1469
* Verdict: Accepted
* Submission Date: 2017-12-10 13:59:22
* Time: 44 MS
* Memory: 2128 KB
*/
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

bool table[100010];

void build()
{
    table[1] = false;
    table[2] = true;
    for (int i = 3; i < 100010; i++)
    {
        int j = 2;
        int range = floor(sqrt(i)) + 1;
        while (i % j && j < range) j++;
        if (j == range) table[i] = true;
        else table[i] = false;
    }

    // for (int i = 1; i <= 100; i++) if (table[i]) cout << i << endl;
}



int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    build();

    int n;
    while (scanf("%d", &n) == 1)
    {
        if (table[n]) printf("Yes.\n");
        else printf("No.\n");
    }
}
