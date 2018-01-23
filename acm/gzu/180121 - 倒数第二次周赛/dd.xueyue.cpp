// Author：Lxy417165709
#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;

char map[6][105];
  
int main()
{
    ll T;
    scanf("%lld",&T);
    while(T--)
    {
        ll num=0;
        memset(map,0,sizeof(map));
        ll mark_num3=0,mark_num4=0,mark_num5=0;
        bool mark3[105]={0};
        bool mark4[105]={0};
        bool mark5[105]={0};
        for(int i=1;i<=4;i++)
        {
            for(int u=1;u<=100;u++)
            {
                scanf(" %c",&map[i][u]);
                if(i==4 && map[i][u]=='#')
                {
                    mark4[u]=1;
                    mark_num4++;
                }
                if(i==3 && map[i][u]=='#')
                {
                    mark3[u]=1;
                    mark_num3++;
                }
            }
        }
         for(int i=1;i<=100;i++)
         {
            if(mark3[i]*mark4[i]==1)
            {
                mark5[i]=1;
                mark_num5++;
            }
        }
        
        for(int i=1;i<=100;i++)
        {
            if(map[1][i]=='*')continue;
            for(int t=1;t<=100;t++)
            {
                if(map[2][t]=='*' || i==t)continue;
                ll j=0;
                ll temp=mark_num5;
                mark_num5=mark_num5-mark5[i]-mark5[t];   	 			
				num=num+(mark_num4-mark4[i]-mark4[t])*(mark_num3-mark3[i]-mark3[t])-mark_num5;
                mark_num5=temp;
            }
        }
        printf("%lld\n",num);
    }
}

