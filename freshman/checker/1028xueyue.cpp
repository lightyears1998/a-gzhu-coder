#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;

string s;

int main()
{
    // �ر����׼io��ͬ�������cin/cout������Ҫ�ڹرպ����cout/printf()��IO��ʽ 
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
                // �����д����ÿ��S[j]��s[i]��Ϻ��ַ�������һ�鲢��ֵ��S[j]
                // S[j] = S[j] + s[i];
                
                S[j] += s[i]; // ֱ����S[j]ĩβ�����ַ� 
            }
        }
        cout<<S[0]<<S[2]<<S[4]<<endl;
        cout<<S[0]<<S[3]<<S[2]<<S[1]<<S[4]<<endl;
    }
}

