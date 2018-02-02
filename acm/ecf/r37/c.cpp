#include <bits/stdc++.h>
using namespace std;

// 换一个顺手的计数法非常重要 

int num[200200];
int sum[200200];
string idt;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif 
	
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
	
	int n; cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> num[i]; 
	}
	cin >> idt;
	for (int i = 1; i < n; ++i) {
		sum[i] += sum[i-1] + idt[i-1]-'0';
	}
	
	bool ok = true;
	for (int i = 1; ok && i <= n; ++i)
	{
		if (num[i] == i) continue;
		if (num[i] < i) {
			if (sum[i-1] - sum[num[i]-1] < i - num[i]) ok = false; 
		}
		if (num[i] > i) {
			if (sum[num[i]-1] - sum[i-1] < num[i] - i) ok = false;
		}
	}
	
	cout << (ok ? "YES" : "NO") << endl;
} 
