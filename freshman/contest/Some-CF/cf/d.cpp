#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

const int maxN = 110000;
const double eps = 1e-8;

int n;
bool mark[maxN];
vector<pi> vec;

bool cmp(pi &a, pi &b)
{
	if (a.first < b.first) return a.first < b.first;
	return a.second < b.second;
}

int check()
{
	int cnt = 0;
	for (int i=0; i<n; ++i) if (!mark[i]) ++cnt;
	return cnt;
}

void judge(int a, int b)
{
	double x1 = vec[a].first, y1 = vec[a].second;
	double x2 = vec[b].first, y2 = vec[b].second;
	for (int i=0; i<n; ++i) if (!mark[i])
	{
		double x3 = vec[i].first, y3 = vec[i].second;
		if (abs(x1-x2)<eps && abs(x2-x3)<eps) {
			mark[i] = true; continue;
		}
		if (abs(x1-x2) < eps) continue;
		if (abs(x2-x3) < eps) continue;
		if (abs((y2-y1)/(x2-x1)-(y3-y1)/(x3-x1)) < eps) mark[i] = true;
	}
}

int main()
{/*
	scanf("%d", &n);
	
	if (n == 1) {
		cout << "YES" << endl; return 0;
	}
	
	for (int i=0; i<n; ++i)
	{
		int x, y; scanf("%d%d", &x, &y);
		vec.push_back({x, y});
	}
	
	sort(vec.begin(), vec.end(), cmp);
	
	bool flag = false;
	for (int i=1; !flag && i<n; ++i)
	{
		memset(mark, 0, sizeof(mark));
		
		mark[0] = mark[i] = true;
		judge(0, i);
		
		int ck = check();
		if (ck == 0 || ck == 1) {
			flag = true; break;
		}
		
		int kdd[2];
		for (int i=0, j=0; i<2 && j<n; ++j) {
			if (!mark[j]) 
				kdd[i++] = j;
		}
		mark[kdd[0]] = mark[kdd[1]] = true;
		judge(kdd[0], kdd[1]); 
		ck = check();
	
		if (ck == 0) {
			flag = true; break;
		}
	}
	
	printf(flag ? "YES\n" : "NO\n");*/
	char s[3];
	scanf("%s",s);
	printf("%s\n",s);
}
