#include <bits/stdc++.h>
using namespace std;

// ����Ƿ��
// Ӧ�߱�����˼ά��Conan��Cnt2���ʱ��ȥ����Cnt3����������������� 

int main()
{
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
	
	int n; cin >> n;
	
	int mx = -1, mx2 = -1;
	int cnt = 0, cnt2 = 0;
	for (int i = 0; i < n; ++i)
	{
		int t; cin >> t;
		if (t == mx) {
			++cnt; continue;
		}
		if (t == mx2) {
			++cnt2; continue;
		}
		if (t > mx) {
			swap(mx, mx2); swap(cnt, cnt2);
			mx = t, cnt = 1;
			continue;
		}
		if (t > mx2) {
			mx2 = t, cnt2 = 1;
			continue;
		}
	}
	
	if (cnt%2)
	{
		cout << "Conan" << endl;
	}
	else
	{
		cout << (cnt2%2 ? "Conan" : "Agasa") << endl;
	}
}
