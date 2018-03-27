#include <bits/stdc++.h>
using namespace std;

int main()
{
	for (int a=2; a<10; ++a) {
		for (int b=0; b<10; ++b) {
			for (int c=0; c<10; ++c) {
				for (int d=0; d<10; ++d) {			
					int num, ten = a+b+c+d;
					int t12 = 0, t16 = 0;
					
					num = a*1000+b*100+c*10+d;
					for (int i=0; i<4; ++i) {
						t12 += num%12;
						num /= 12;
					}
					
					num = a*1000+b*100+c*10+d;
					for (int i=0; i<4; ++i) {
						t16 += num%16;
						num /= 16;
					}
					
					if (ten == t12 && t12 == t16) {
						cout << a*1000+b*100+c*10+d << endl;
					}
				} 
			}
		}
	}
}
