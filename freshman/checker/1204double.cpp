#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include<stdio.h>  
#include<string.h>  
using namespace std;

int a[10010];
int main()
{
	a[1] = 1;
	long long sum, m;
	for (int i = 2; i <= 10000; i++)
		a[i] = a[i - 1] + i;
		
	while (cin >> m)
	{
		sum = 0; 
		for (int i = 1; i <= 10000; i++)
		{
			sum += a[i];
			if (sum>m)
			{
				cout << (i-1) << endl;
				break;
			}
		}
	}
	return 0;
}
