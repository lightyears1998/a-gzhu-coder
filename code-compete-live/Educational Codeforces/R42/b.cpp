#include <bits/stdc++.h>
using namespace std;

vector<int> cons;

int main()
{
	int n, a, b; cin >> n >> a >> b;
	string seat; cin >> seat; seat += '*';
	
	int cnt = 0;
	for (char &ch : seat) {
		if (ch == '.') {
			++cnt;
		}
		else if (cnt) {
			cons.push_back(cnt), cnt = 0;
		}
	}
	
	int ans = 0;
	for (int cnt : cons) {
		int arr = cnt/2;
		if (a) {
			ans += min(a, arr);
			a -= min(a, arr);
		}
		if (b) {
			ans += min(b, arr);
			b -= min(b, arr);
		}
		if (cnt&1 && (a || b)) {
			ans += 1;
			(a>b? a : b)--; 
		}
	}
	cout << ans << endl;
}
