#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

signed main() {
#ifdef LOCAL
  assert(freopen("test.in", "r", stdin));
#endif
  int n;
  cin >> n;
  ll pr = -1e12;
  ll gmin = 1e12, gmax = -1e12;
  ll bmin = 1e12, bmax = -1e12;
  ll rmin = 1e12, rmax = -1e12;
  vector<int> p[2];
  ll res = 0;
  for (int i = 0; i <= n; ++i) {
    ll x;
    char c;
    if (i < n) {
      cin >> x >> c;
    } else {
      x = 1e12, c = 'G';
    }
    if (c == 'G') {
      if (i < n) {
        gmin = min<ll>(gmin, x);
        gmax = max<ll>(gmax, x);
      }
      ll cur1 = x - pr, cur2 = (x - pr) * 2;
      if (cur1 >= 1e11) {
        cur1 = 0;
      }
      for (int q = 0; q < 2; ++q) {
        if (!p[q].empty()) {
          cur1 += x - pr;
          ll mx = max<ll>(p[q].front() - pr, x - p[q].back());
          for (int j = 0; j < (int) p[q].size() - 1; ++j) {
            mx = max<ll>(mx, p[q][j + 1] - p[q][j]);
          }
          cur1 -= mx;
          p[q].clear();
        }
      }
      res += min(cur1, cur2);
      pr = x;
    } else if (c == 'R') {
      p[0].push_back(x);
      rmin = min<ll>(rmin, x);
      rmax = max<ll>(rmax, x);
    } else {
      p[1].push_back(x);
      bmin = min<ll>(bmin, x);
      bmax = max<ll>(bmax, x);
    }
  }
  if (gmin > gmax) {
    ll res = 0;
    if (rmin < rmax) {
      res += rmax - rmin;
    }
    if (bmin < bmax) {
      res += bmax - bmin;
    }
    cout << res << '\n';
    return 0;
  }
  cout << res << '\n';
}