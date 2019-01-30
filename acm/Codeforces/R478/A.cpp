#include <bits/stdc++.h>
using namespace std;

#define sfi(n) scanf("%d", &n)
#define sfc(n) scanf(" %c", &n) 
#define rep(i, a, b) for (int i=a; i<b; ++i)
#define dwn(i, b, a) for (int i=b-1; i>=a; --i)

set<string> st;

int main()
{
	int n; cin >> n;
	while (n--) {
		string str; cin >> str;
		sort(str.begin(), str.end());
		str.resize(unique(str.begin(), str.end())-str.begin());
		st.insert(str);
	}
	cout << st.size() << endl;
}
