/*
* this code is made by lightyears
* Problem: 1524
* Verdict: Accepted
* Submission Date: 2018-04-10 15:48:14
* Time: 68 MS
* Memory: 2020 KB
*/
#include <bits/stdc++.h>
using namespace std;
 
char buf[20];
int num[20], tot;
 
int get(int bgn, int end)
{
    // bool zero = false;
     
    int sum = 0;
    for (int i=bgn; i<=end; ++i) {
        // if (!num[i] && zero) return -1;
        // if (!num[i]) zero = true;
         
        sum = sum*10 + num[i];
    }
    if (!num[bgn] && sum) return -1;
    if (!sum && end-bgn) return -1;
    return sum;
}
 
void print(int bgn, int end) {
    for (int i=bgn; i<=end; ++i) {
        putchar(num[i]+'0');
    }
}
 
bool match(int num) {
    return 0 <= num && num <= 255;
}
 
void search()
{
    for (int i=0; i<tot; ++i)
    {
        int a = get(0, i);
        if (!match(a)) continue;
         
        for (int j=i+1; j<tot; ++j)
        {
            int b = get(i+1, j);
            if (!match(b)) continue;
             
            for (int k=j+1; k<tot; ++k)
            {
                if (k+1==tot) continue;
                 
                int c = get(j+1, k);
                int d = get(k+1, tot-1);
                if (!match(c) || !match(d)) continue;
                 
                print(0, i); putchar('.');
                print(i+1, j); putchar('.');
                print(j+1, k); putchar('.');
                print(k+1, tot-1); putchar('\n');
            }
        }
    }
}
 
int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif
     
    int t; scanf("%d", &t);
    while (t--) {
        tot = 0;
         
        scanf("%s", buf);
        for (int i=0; buf[i]; ++i) {
            num[tot++] = buf[i]-'0';
        }
         
        search();
        putchar('\n');
    }
}