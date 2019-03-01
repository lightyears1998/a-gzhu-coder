/*
* this code is made by lightyears
* Problem: 1516
* Verdict: Accepted
* Submission Date: 2018-04-10 16:21:43
* Time: 96 MS
* Memory: 2028 KB
*/
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
 
set<LL> st;
 
int main()
{
    LL a=3, b=5, sum;
    st.insert(2); st.insert(3); st.insert(5);
    while ((sum=a+b)<=9223372036854775807LL && sum>0) {
        a = b, b = sum;
        st.insert(sum);
    }
     
    int t; scanf("%d", &t);
    while (t--)
    {
        LL n; scanf("%lld", &n);
        if (st.find(n) != st.end()) {
            puts("Lose...");
        }
        else puts("Win!");
    }
}