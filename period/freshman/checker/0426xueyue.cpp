// 巧了，C++11之前，STL里面有个函数人称distance() 
// Namespace Problem
#include<iostream>
#include<cmath>
#include<string>
#include<iomanip>
#include<cstdio>
#include<algorithm>
#include<string>
#include<queue> 
#include<map>
#include<set>
#include<cstring> 
#include<ctime>
#define inf 1e15
#define eps 1e-8
using namespace std;

typedef long long ll;

struct _node
{
	ll x,y;

}E[10500];



double dist(_node a,_node b)  // 原名distance() 
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

set<ll> V;
set<ll>::iterator it;
ll A[1050];
ll ff(ll a)
{
	if(a==A[a])return a;
	else return A[a]=ff(A[a]);
}
int main()  
{
	ll n,d;
	scanf("%lld%lld",&n,&d);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&E[i].x,&E[i].y);
		A[i]=i;
	}
	ll fi,fa;

	char ch;
	ll a,b;
	while(cin>>ch)
	{
	
		if(ch=='O')
		{
			scanf("%lld",&a);
			V.insert(a);
			it=V.begin();
			for(;it!=V.end();it++)
			{
				double dis=dist(E[a],E[*it]);  // STL里面有个函数叫做distance()...  
		
				if(dis<=d+eps)
				{
					fi=ff(*it);
					fa=ff(a);
					if(fi<fa)A[fa]=fi;
					else A[fi]=fa;
				}
			}
				
		}
		if(ch=='S')
		{
			scanf("%lld%lld",&a,&b);
		
			if(ff(a)==ff(b))printf("SUCCESS\n");
			else printf("FAIL\n"); 
		}
	}
}
