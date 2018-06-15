#include <bits/stdc++.h>
using namespace std;

const int maxN = 1010;

string entry, a, b;
string ans;

int main()
{
	cin >> entry >> a >> b;
	
	reverse(entry.begin(), entry.end());
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
   	
	unsigned cent = 0, ca = 0, cb = 0;
	int x = 0;
	for (; ca<a.size() || cb<b.size() || x; ++cent, ++ca, ++cb)
	{
		int left = (ca<a.size() ? a[ca]-'0' : 0);
		int rght = (cb<b.size() ? b[cb]-'0' : 0);
		int entr = (cent<entry.size() ? entry[cent]-'0' : 0);
		if (entr == 0) entr = 10;
		
		int sum = left + rght + x;
		if (sum >= entr) {
			x = sum/entr;
			sum %= entr;
		}
		else x = 0;
		ans.push_back(char(sum+'0'));
	}
	
	int tot;
	for (tot = ans.size()-1; tot >= 0; --tot) {
		if (ans[tot] == '0') continue;
		else break;
	}
	
	if (tot == -1) {
		printf("0\n");
	}
	else {
		while (tot >= 0) {
			cout << ans[tot--];
		}
		cout << endl;
	}
}
