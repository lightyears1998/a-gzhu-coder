#include<cstring>
#include<cstdio>
#include<iostream>
using namespace std;
const int maxn = 45;

int a[maxn][maxn];

int main()
{
    int n;
    scanf("%d", &n);
    while(n--)
    {
        int tot=1; 
        int t, x=0, y=0;
        scanf("%d", &t);
        memset(a, 0, sizeof(a));
        a[x][y]=6;

        while(tot<t*t)
        {
            while(y+1<t && (a[x][y+1]==0) && a[x][y+2]!=6 &&a[x-1][y+1]!=6) {a[x][++y] = 6; ++tot;}
            while(y+1<t && (a[x][y+1]==0) && (a[x][y+2]==6||a[x-1][y+1]==6) ) {a[x][++y] = 1; ++tot;}
    
            while(x+1<t && (a[x+1][y]==0) && a[x+2][y]!=6 && a[x+1][y-1]!=6 && a[x+1][y+1]!=6) {a[++x][y] = 6; ++tot;}
            while(x+1<t && (a[x+1][y]==0) && (a[x+2][y]==6 || a[x+1][y-1]==6 || a[x+1][y+1]==6)) {a[++x][y] = 1; ++tot;}
    
            while(y>=1 && (a[x][y-1]==0) && a[x][y-2]!=6 &&a[x-1][y-1]!=6&&a[x+1][y-1]!=6) {a[x][--y] = 6; ++tot;}
            while(y>=1 && (a[x][y-1]==0) && (a[x][y-2]==6 ||a[x-1][y-1]!=6||a[x+1][y-1]!=6)) {a[x][--y] = 1; ++tot;}
    
            while(x>=1 && (a[x-1][y]==0) && a[x-2][y]!=6  && a[x-1][y+1]!=6 && a[x-1][y-1]!=6) {a[--x][y] = 6; ++tot;}
            while(x>=1 && (a[x-1][y]==0) && (a[x-2][y]==6  || a[x-1][y+1]==6 || a[x-1][y-1]==6)) {a[--x][y] = 1; ++tot;}
            if (~x&1) a[x][y] = 6;
        }
    
        if (t%4==0) a[t/2][(t-1)/2] = 1;
    
        for(int i=0; i<t; ++i)
        {
            for(int j=0; j<t; ++j)
            {
                if(a[i][j]==1) printf(" ");
                else printf("%d", a[i][j]);
            }
            printf("\n");
        }
    }
}
