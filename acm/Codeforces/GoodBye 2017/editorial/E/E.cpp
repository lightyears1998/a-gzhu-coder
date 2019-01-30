#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int mod = 1e9 + 7;
template<typename T>
T add(T x) {
  return x;
}
template<typename T, typename... Ts>
T add(T x, Ts... y) {
  T res = x + add(y...);
  if (res >= mod)
    res -= mod;
  return res;
}
template<typename T, typename... Ts>
T sub(T x, Ts... y) {
  return add(x, mod - add(y...));
}
template<typename T, typename... Ts>
void udd(T &x, Ts... y) {
  x = add(x, y...);
}
template<typename T>
T mul(T x) {
  return x;
}
template<typename T, typename... Ts>
T mul(T x, Ts... y) {
  return (x * 1ll * mul(y...)) % mod;
}
template<typename T, typename... Ts>
void uul(T &x, Ts... y) {
  x = mul(x, y...);
}
int bin(int a, ll deg) {
  int r = 1;
  while (deg) {
    if (deg & 1)
      uul(r, a);
    deg >>= 1;
    uul(a, a);
  }
  return r;
}
int inv(int x) {
  assert(x);
  return bin(x, mod - 2);
}

const int maxn = 1005;
int b[maxn][maxn];
int bsum[maxn];

void pre() {
  b[0][0] = 1;
  for (int i = 0; i < maxn - 1; ++i) {
    for (int j = 0; j <= i; ++j) {
      udd(bsum[i], b[i][j]);
      udd(b[i + 1][j], mul(b[i][j], j));
      udd(b[i + 1][j + 1], b[i][j]);
    }
  }
}

signed main() {
#ifdef LOCAL
  assert(freopen("test.in", "r", stdin));
#endif
  pre();
  int m, n;
  cin >> m >> n;
  vector<string> v(m, string(n, ' '));
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < m; ++j) {
      v[j][i] = s[j];
    }
  }
  sort(v.begin(), v.end());
  int res = 1;
  for (int i = 0; i < m; ++i) {
    int r = i;
    while (r < m && v[r] == v[i]) {
      ++r;
    }
    cerr << "cnt: " << r - i << '\n';
    uul(res, bsum[r - i]);
    i = r - 1;
  }
  cout << res << '\n';
}