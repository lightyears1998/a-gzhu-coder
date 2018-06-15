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
        priority_queue<ll,vector<ll>,less<ll> > Q;	//�Ӵ�С���� 
         
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
            scanf("%lld",&a);//��Ʒ�۸� 
            Q.push(a);	//����Ʒ����Q 
            sum=sum+a;//�����������˵ļ۸� 
        }
        
      
      
      
        ll zks;//��Ѽ��� 
        while(n>0)
        {
            if(n>=mini)	//�������ۿ�ʱ 
            {
                zks=n-mini;
                if(zks>2)zks=2;	//��ѵ����2�� 
                
                for(int u=1;u<=mini;u++)Q.pop();  // ������Ʒ 
                for(int u=1;u<=zks;u++)
                {
                    sum=sum-Q.top(); //��ȥ��ѵļ۸� 
                    Q.pop();	
                }
                
                n=n-mini-zks;	
            }
            else n=0; //û�ۿ���ֱ���˳�      
        }
        printf("%lld\n",sum);          
	}
}
