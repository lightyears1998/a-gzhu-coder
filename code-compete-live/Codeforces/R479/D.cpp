#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int maxN = 110;

int n;
LL num[maxN];
LL build[maxN];
bool used[maxN];

bool check(int idx, LL num)
{
	if (idx == 0) return true;
	if (build[idx-1]%3==0 && build[idx-1]/3==num) return true;
	if (build[idx-1]*2 == num) return true;
	return false;
}

bool search(int cur) 
{
	if (cur == n) return true;
	for (int i=0; i<n; ++i) {
		if (!used[i] && check(cur, num[i])) {
			build[cur] = num[i];
			used[i] = true;
			
			if (search(cur + 1)) {
				return true;
			}
			else {
				used[i] = false;
				continue;
			}
		}
	}
	return false;
}

int main()
{
	cin >> n;
	for (int i=0; i<n; ++i) {
		cin >> num[i];
	}
	sort(num, num+n);
	
	search(0);
	for (int i=0; i<n; ++i) {
		if (i) cout << ' ';
		cout << build[i];
	}
}
