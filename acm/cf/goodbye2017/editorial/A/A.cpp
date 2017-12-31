#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

signed main() {
#ifdef LOCAL
  assert(freopen("test.in", "r", stdin));
#endif
  string s;
  cin >> s;
  int res = 0;
  string v = "aeiou";
  for (auto c : s) {
    if (find(v.begin(), v.end(), c) != v.end() || (isdigit(c) && (c - '0') % 2))
      ++res;
  }
  cout << res << '\n';
}