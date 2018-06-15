#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t; scanf("%d", &t);
	while (t--)
	{	
		int ap[6], al[6];
		for (int i=1; i<=5; ++i) {
			int d, b[5], l[5]; 
			scanf("%d%d%d%d%d", &d, &b[1], &b[2], &b[3], &b[4]);
			for (int k=1; k<=4; ++k) {
				l[b[k]] = k;
			}
			if (i == 1) {
				if (d == 1) ap[i] = 2; 
				if (d == 2) ap[i] = 2;
				if (d == 3) ap[i] = 3;
				if (d == 4) ap[i] = 4;
			}
			if (i == 2) {
				if (d == 1) ap[i] = l[4]; 
				if (d == 2) ap[i] = ap[1];
				if (d == 3) ap[i] = 1;
				if (d == 4) ap[i] = ap[1];			
			}
			if (i == 3) {
				if (d == 1) ap[i] = l[al[2]];
				if (d == 2) ap[i] = l[al[1]];
				if (d == 3) ap[i] = 3;
				if (d == 4) ap[i] = l[4];
			}
			if (i == 4) {
				if (d == 1) ap[i] = ap[1]; 
				if (d == 2) ap[i] = 1;
				if (d == 3) ap[i] = ap[2];
				if (d == 4) ap[i] = ap[2];	
			}
			if (i == 5) {
				if (d == 1) ap[i] = l[al[1]]; 
				if (d == 2) ap[i] = l[al[2]];
				if (d == 3) ap[i] = l[al[4]];
				if (d == 4) ap[i] = l[al[3]];				
			}
			al[i] = b[ap[i]];
			printf("%d %d\n", ap[i], al[i]);
		}
	}
}
