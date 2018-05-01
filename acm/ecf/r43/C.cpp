#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

const int maxN = 3e5+5;

int idx[maxN];
vector<pi> vec;

bool cmp(int i, int j) {
	if (vec[i].first != vec[j].first) {
		return vec[i].first < vec[j].first;
	}
	return vec[i].second < vec[j].second;
}

int main()
{
	int n; cin >> n;
	idx[0] = 0; vec.push_back({-1, -1});
	for (int i=0; i<n; ++i) {
		int a, b; cin >> a >> b;
		idx[i+1] = i+1;
		vec.push_back({a, b});
	}
	sort(idx, idx+n+1, cmp);
	
//	for (int i=0; i<=n; ++i) {
//		cout << idx[i] << endl;
//		cout << vec[idx[i]].first << ' ' << vec[idx[i]].second << endl;	
//	}
	
	int id_l, mn_l = -1, mx_r=-1;
	for (int i=1; i<=n; ++i) {
		if (vec[idx[i]].second <= mx_r) {
			cout << idx[i] << ' ' << id_l << endl;
			return 0;
		}
		else {
			if (mn_l == vec[idx[i]].first) {
				cout << id_l << ' ' << idx[i] << endl;
				return 0;
			}
			else {
				id_l = idx[i]; 
				mn_l = vec[idx[i]].first;
				mx_r = vec[idx[i]].second;
			}
		}
	}
	cout << -1 << ' ' << -1 << endl;
}
