#include<queue>
#include<cstdio>
#include<iostream>
using namespace std;
typedef long long ll;

int main() 
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif
	
    ll m,n,q,a;
    
    while(scanf("%lld",&m) == 1)
    {
        priority_queue<ll,vector<ll>,less<ll> > Q;	//从大到小排序 
         
        ll sum=0;
        ll mini=1000000000;
      
        while(m--)
        {
            scanf("%lld",&q);
            mini=min(mini,q);
        }
     
        scanf("%lld",&n);
      
      
        for(int i=1;i<=n;i++)
        {
            scanf("%lld",&a);//物品价格 
            Q.push(a);	//把物品推入Q 
            sum=sum+a;//把所有有买了的价格 
        }
        
      
      
      
        ll zks;//免费件数 
        while(n>0)
        {
            if(n>=mini)	//可以有折扣时 
            {
                zks=n-mini;
                if(zks>2)zks=2;	//免费的最多2件 
                
                for(int u=1;u<=mini;u++)Q.pop();  // 购买物品 
                for(int u=1;u<=zks;u++)
                {
                    sum=sum-Q.top(); //减去免费的价格 
                    Q.pop();	
                }
                
                n=n-mini-zks;	
            }
            else n=0; //没折扣则直接退出      
        }
        printf("%lld\n",sum);          
	}
}
