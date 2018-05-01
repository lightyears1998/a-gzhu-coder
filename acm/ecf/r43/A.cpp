#include <bits/stdc++.h>
using namespace std;

int main()
{
	string s; cin >> s >> s;
	
	int cnt0 = 0, cnt1 = 0;
	for (char &ch : s) {
		if (ch == '0') ++cnt0;
		if (ch == '1') ++cnt1;
	}
	
	if (cnt1 > 1) cnt1 = 1;
	for (int i=0; i<cnt1; ++i) cout << '1';
	for (int i=0; i<cnt0; ++i) cout << '0';
	cout << endl;
} 
