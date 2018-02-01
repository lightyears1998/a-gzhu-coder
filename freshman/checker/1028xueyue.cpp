#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;

string s;

int main()
{
    // 关闭与标准io的同步会加速cin/cout，但不要在关闭后混用cout/printf()等IO方式 
    // cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);

    ll n;
    cin >> n; getline(cin, s); 
    while(n--)
    {
        string S[10];
        
        getline(cin,s);
        ll j=0;
        for(unsigned i=0; i<s.length(); i++)
        {
            if(s[i]=='<' || s[i]=='>')
            {
                j++;
            }
            else
            {
                if(s[i]=='\n' || s[i]=='\r') break;
                // 下面的写法，每次S[j]与s[i]结合后，字符串复制一遍并赋值给S[j]
                // S[j] = S[j] + s[i];
                
                S[j] += s[i]; // 直接向S[j]末尾插入字符 
            }
        }
        cout<<S[0]<<S[2]<<S[4]<<endl;
        cout<<S[0]<<S[3]<<S[2]<<S[1]<<S[4]<<endl;
    }
}

