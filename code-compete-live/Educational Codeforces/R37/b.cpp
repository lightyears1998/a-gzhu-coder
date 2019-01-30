#include <bits/stdc++.h>
using namespace std;

struct student
{
	int idx;
	int l, r, t;
} stu[1010];

bool cmp_l(student a, student b)
{
	if (a.l != b.l)
		return a.l < b.l;
	return a.idx < b.idx;
}

bool cmp_idx(student a, student b)
{
	return a.idx < b.idx;
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif
	
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
	
	int t; cin >> t;
	while (t--)
	{
		memset(stu, 0, sizeof(stu));
		
		int n; cin >> n;
		for (int i = 1; i <=n; ++i)
		{
			stu[i].idx = i;
			cin >> stu[i].l >> stu[i].r;
		}
		
		sort(stu+1, stu+1+n, cmp_l);
		int t = 1;
		for (int i = 1; i <= n; ++i) 
		{
			if (t>stu[i].r) {
				stu[i].t = 0;
				continue;
			}
			if (t<stu[i].l) {
				t = stu[i].l;
			}
			if (t>=stu[i].l) {
				stu[i].t = t;
				++t;
			}
		}
		
		sort(stu+1, stu+1+n, cmp_idx);
		for (int i = 1; i <=n; ++i)
		{
			cout << stu[i].t << ' ';
		}
		cout << endl;
	}
}
