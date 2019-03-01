/*
* this code is made by lightyears
* Problem: 1515
* Verdict: Accepted
* Submission Date: 2018-04-10 14:23:53
* Time: 0 MS
* Memory: 2020 KB
*/
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
 
const LL mod = 1e9+7;
 
struct Matrix
{
    LL v[2][2];
     
    Matrix() {
        memset(v, 0, sizeof(v));
    }
    Matrix(int a, int b, int c, int d) {
        v[0][0] = a, v[0][1] = b;
        v[1][0] = c, v[1][1] = d;
    }
     
    Matrix operator * (const Matrix m) const
    {
        Matrix tmp;
         
        for (int i=0; i<2; ++i) {
            for (int j=0; j<2; ++j) {
                for (int k=0; k<2; ++k) {
                    tmp.v[i][j] += v[i][k]*m.v[k][j];
                    tmp.v[i][j] %= mod;
                }
            }
        }  
        return tmp;
    }
     
    void print() {
        for (int i=0; i<2; ++i) {
            for (int j=0; j<2; ++j) {
                cout << v[i][j] << ' ';
            }
            cout << endl;
        }
    }
};
 
Matrix fpow(int n)
{
    Matrix ans(1, 0, 0, 1), base(1, 1, 1, 0);
    while (n) {
        if (n&1) {
            ans = ans * base;
        }
        base = base * base;
        n >>= 1;
    }
    return ans;
}
 
int main()
{  
    int t; scanf("%d", &t);
    while (t--)
    {
        int n; scanf("%d", &n);
         
        if (n == 1) {
            printf("2\n"); continue;
        }
        if (n == 2) {
            printf("1\n"); continue;
        }
         
        Matrix m = fpow(n-2);
        printf("%lld\n", (m.v[0][0]+2*m.v[0][1])%mod);
    }
}