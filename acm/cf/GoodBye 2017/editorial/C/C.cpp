#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int maxn = 2018;
ld x[maxn];
ld y[maxn];

signed main() {
#ifdef LOCAL
  assert(freopen("test.in", "r", stdin));
#endif
  cout << fixed;
  cout.precision(10);
  int n;
  ld r;
  cin >> n >> r;
  for (int i = 0; i < n; ++i) {
    cin >> x[i];
    ld my = r;
    for (int j = 0; j < i; ++j) {
      if (fabsl(x[i] - x[j]) > 2 * r) {
        continue;
      }
      auto sqr = [](ld x) { return x * x; };
      ld cy = y[j] + sqrtl(sqr(2 * r) - sqr(x[i] - x[j]));
      my = max(my, cy);
    }
    y[i] = my;
    cout << my << ' ';
  }
  cout << '\n';
}