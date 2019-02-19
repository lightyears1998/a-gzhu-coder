#include <bits/stdc++.h>
using namespace std;

vector<int> bulket;

void split(long long n)
{
	int i = 0;
	while (n)
	{
		if (n&1) bulket.push_back(i);
		n >>= 1, ++i;
	}
	sort(bulket.begin(), bulket.end(), greater<int>());
}

int main()
{
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
	
	long long n, k; cin >> n >> k;
	split(n);
	
	if (bulket.size() > k) cout << "No" << endl;
	else
	{
		while (bulket.size() < k) {
			vector<int>::iterator it;
			for (it = bulket.begin(); it != bulket.end() && bulket.size() < k; it += 2)
			{
				int t = *it - 1;
				bulket.erase(it);
				bulket.insert(it, t), bulket.insert(it, t);
			}
		}
		if (bulket.size() == k) 
		{
			cout << "Yes" << endl;
			for (int i : bulket) cout << i << ' ';
			cout << endl; 
		}
		else cout << "No" << endl;
	}
}
