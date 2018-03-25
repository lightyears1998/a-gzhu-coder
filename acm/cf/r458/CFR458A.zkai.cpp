#include<algorithm>
#include<cmath>
#include<vector>
#include<iostream>
using namespace std;

int s[1050];

int main()
{
	int i;
	int num;
	scanf("%d\n", &num);
	for(i=0; i<num; i++)
	{
		int t; scanf("%d", &t);
		s[i] = t; 	
	}
	
	sort(s, s+num);
	
	int j;
	for(j=i-1; j>=0; j--)
	{
		double som = floor(sqrt(s[j]));
		if (s[j] < 0) break;
        if (abs(sqrt(s[j])-som) > 1e-6) break;
	}
	printf("%d\n", s[j]);
}

