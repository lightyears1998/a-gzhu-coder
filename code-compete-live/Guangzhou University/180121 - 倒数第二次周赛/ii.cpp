#include<bits/stdc++.h>
using namespace std;

// Idea Author: DaP

int dir[6][24]={
	{ 1, 3, 0, 2,17,19, 6, 7, 8, 9,10,11,12,13,20,22,16,15,18,14, 5,21, 4,23},  
	{ 2, 0, 3, 1,22,20, 6, 7, 8, 9,10,11,12,13,19,17,16, 4,18, 5,14,21,15,23},
	{12, 1,14, 3, 0, 5, 2, 7, 4, 9, 6,11, 8,13,10,15,18,16,19,17,20,21,22,23},
	{ 4, 1, 6, 3, 8, 5,10, 7,12, 9,14,11, 0,13, 2,15,17,19,16,18,20,21,22,23},
	{20,21, 2, 3, 4, 5, 6, 7, 8, 9,17,16,14,12,15,13, 0, 1,18,19,11,10,22,23},
	{16,17, 2, 3, 4, 5, 6, 7, 8, 9,21,20,13,15,12,14,11,10,18,19, 0, 1,22,23},
};

bool f(int n,int MM[])
{
	int num=0,i,j;
	if(MM[0]==MM[1]&&MM[0]==MM[2]&&MM[0]==MM[3])  
		num++;
	if(MM[4]==MM[5]&&MM[4]==MM[6]&&MM[4]==MM[7])  
		num++;
	if(MM[12]==MM[13]&&MM[12]==MM[14]&&MM[12]==MM[15])	
		num++;
	if(MM[8]==MM[9]&&MM[8]==MM[10]&&MM[8]==MM[11])	
		num++;
	if(MM[17]==MM[19]&&MM[17]==MM[16]&&MM[17]==MM[18])	
		num++;
	if(MM[20]==MM[22]&&MM[20]==MM[21]&&MM[20]==MM[23])	
		num++;
	if(num==6) return 1;
	if(n==0) return 0;
	
	int M[25];
	for(i=0;i<6;i++)  
	{
		for(j=0;j<24;j++)  
		{
			M[j]=MM[dir[i][j]];	 
		}
		bool flag = f(n-1,M);
		if (flag) return flag;
	}
}

int main()	
{  
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif
	int t,i,j; scanf("%d",&t); 
	int MAP[25];
	while(t--)
	{
		for(i=0;i<24;i++)  
		{
			scanf("%d", &MAP[i]);
		}
		printf(f(2,MAP)?"YES\n":"NO\n");
	}
}
