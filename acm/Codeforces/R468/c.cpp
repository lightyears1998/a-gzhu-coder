#include <bits/stdc++.h>
using namespace std;

int num[100100];

int main()
{
	int n; cin >> n;
	for (int i = 0; i < n; ++i) cin >> num[i];
	
	int high = *max_element(num, num+n); 
	int low = *min_element(num, num+n);
	if (high - low == 0)
	{
		cout << n << endl;
		for (int i = 0; i < n; ++i) cout << num[0] << ' ';
		cout << endl;
	}
	else if (high - low == 1)
	{
		cout << n << endl;
		for (int i = 0; i < n; ++i) cout << num[i] << ' ';
		cout << endl;
	}
	else
	{
		int ol = 0, om = 0, oh = 0;
		for (int i = 0; i < n; ++i) {
			if (num[i] == high) ++oh;
			else if (num[i] == low) ++ol;
			else ++om;
		}
		int gomid = om + max(ol, oh) - min(ol, oh);
		int goout = ol + oh + om%2;
		
		if (gomid > goout) {
			ol += om/2, oh += om/2, om %= 2;
			cout << goout << endl;
		}
		else {
			int diff = min(ol, oh);
			om += diff * 2, ol -= diff, oh -= diff; 
			cout << gomid << endl;
		}
		while (ol) cout << low << ' ', --ol;
		while (om) cout << low+1 << ' ', --om;
		while (oh) cout << high << ' ', --oh;
		cout << endl;
	}
} 
