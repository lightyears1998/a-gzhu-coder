/*
* this code is made by 1706300001
* Problem: 1467
* Verdict: Accepted
* Submission Date: 2017-12-10 15:09:52
* Time: 40 MS
* Memory: 2020 KB
*/
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        if (n % 3) printf("Minami Win!\n");
        else printf("Aoi Win!\n");
    }
}
