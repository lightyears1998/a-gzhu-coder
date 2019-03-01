/*
* this code is made by lightyears
* Problem: 1512
* Verdict: Accepted
* Submission Date: 2018-04-10 13:18:01
* Time: 0 MS
* Memory: 2024 KB
*/
#include <bits/stdc++.h>
using namespace std;
 
const int maxN = 1010;
 
bool isprime[maxN];
int prime[maxN], tot;
 
void seive()
{
    memset(isprime, true, sizeof(prime));
    isprime[0] = isprime[1] = false;
    for (int i=2; i<maxN; ++i)
    {
        if (isprime[i]) {
            prime[tot++] = i;
            for (int j=1; i*j < maxN; ++j)
                isprime[i*j] = false;
        }
    }
}
 
int main()
{
    seive();
     
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
         
        for (int i=0; i<tot; ++i) {
            if (n % prime[i] == 0) {
                printf("%d\n", prime[i]);
                break;
            }
        }
    }
}