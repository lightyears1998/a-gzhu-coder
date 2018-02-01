#include <bits/stdc++.h>
using namespace std; 
using pt = pair<int, int>;
using wl = pair<pt, pt>;

int i, W, N, M, x, y, C, D, K, E; 

queue<pt> que;
map<pt, bool> key;
map<pt, bool> ext;
map<wl, bool> door;
map<wl, bool> blocked;
map<pt, pt> front;
map<pt, bool> vis;
stack<pt> stk;
int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
string msg[4] = {"move-right", "move-left", "move-down", "move-up"};

bool check(pt bgn, pt dst)
{
	if (dst.first < 0 || dst.first >= N || dst.second < 0 || dst.second >= M || vis[dst])
		return false;
	return door[make_pair(bgn, dst)];
	return !blocked[make_pair(bgn, dst)];
} 

void speak()
{
	pt cur = stk.top();
	while (cur.first != x || cur.second != y)
	{
		cur = front[cur];
		stk.push(cur); 
	}
	
	cur = stk.top(); stk.pop();
	while (!stk.empty()) {
		pt nxt = stk.top(); stk.pop();
		for (int i = 0; i < 4; ++i)
		{
			if (nxt.first-cur.first==dir[i][0] && nxt.second-cur.second==dir[i][1])
				cout << msg[i] << endl;
			if (door[nxt]) cout << "take" << endl;
		}
		cur = nxt;
	}
}

void solve()
{
	pt bgn = make_pair(x, y);
	que.push(bgn);
	front[bgn] = bgn;
	vis[bgn] = true;
	
	while (!que.empty())
	{	
		pt bgn = que.front(); que.pop();
		
		if (ext[bgn]) {
			stk.push(bgn);
			speak();
			return;
		}
		
		for (int i = 0; i < 4; ++i)
		{
			pt nxt = bgn;
			nxt.first += dir[i][0], nxt.second += dir[i][1];
			if (check(bgn, nxt)) {
				front[nxt] = bgn;
				que.push(nxt);
				vis[nxt] = true;
			}
		}
	}
}

int main()
{
	#ifdef LOCAL
	freopen("input-4.txt", "r", stdin);
	freopen("output-4-path.txt", "w", stdout);
	#endif
	
	cin >> i >> W >> N >> M >> x >> y >> C >> D >> K >> E;
	
	while (C--)
	{
		int a, b, c, d; cin >> a >> b >> c >> d; 
		pt x = make_pair(a, b);
		pt y = make_pair(c, d);
		wl w = make_pair(x, y);
		wl l = make_pair(y, x);
		blocked[w] = true;
		blocked[l] = true;
	}
	
	while (D--)
	{
		int a, b, c, d; cin >> a >> b >> c >> d; 
		pt x = make_pair(a, b);
		pt y = make_pair(c, d);
		wl w = make_pair(x, y);
		wl l = make_pair(y, x);
		blocked[w] = true;
		blocked[l] = true;
		door[w] = true;
		door[l] = true;
	}
	
	while (K--)
	{
		int a, b; cin >> a >> b;
		pt x = make_pair(a, b);
		key[x] = true; 
	} 
	
	while (E--)
	{
		int a, b; cin >> a >> b;
		pt x = make_pair(a, b);
		ext[x] = true;
	} 
	
	solve();
}

