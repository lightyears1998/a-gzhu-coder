#include <bits/stdc++.h>
using namespace std;

// ����˼ά 
// Conanֻ���������־�����ż����ʱ��� 
 
int cnt[100010];

int main()
{
	int n; cin >> n; 
	
	for (int i = 0; i < n; ++i)
	{
		int t; cin >> t;
		++cnt[t]; 
	}
	
	int odd = 0; 
	for (int i = 0; i < 100010; ++i) {
		if (cnt[i]%2) ++odd; 
	}
	
	cout << (odd ? "Conan" : "Agasa") << endl; 
} 
