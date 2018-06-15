#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n; cin >> n;
	while (n--) {
		double h, w; cin >> h >> w; w/=2;
		double standard = (h-100)*0.9;
		bool perfect = abs(w-standard) < standard*0.1;
		if (perfect) 
			cout << "You are wan mei!" << endl;
		else if (w<standard) 
			cout << "You are tai shou le!" << endl;
		else if (w>standard) 
			cout << "You are tai pang le!" << endl;
	}
}
