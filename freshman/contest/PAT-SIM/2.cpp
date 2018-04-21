#include <bits/stdc++.h>
using namespace std;

int main()
{
	int hh, mm; scanf("%d:%d", &hh, &mm);
	
	bool dang = true;
	if (hh-12<0 || (hh==12&&mm==0))
		dang = false;

	int cnt = hh-12;
	if (mm>0) ++cnt;
	
	if (!dang) 
		printf("Only %02d:%02d.  Too early to Dang.\n", hh, mm);
	else {
		for (int i=0; i<cnt; ++i) {
			printf("Dang");
		}
		putchar('\n');
	}
}
