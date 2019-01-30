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
int d[maxn][maxn];
int k;
int pa, pb;

int calc(int n, int m) {
  if (m >= k) {
    return m;
  }
  assert(n <= k);
  if (n == k) {
    int mean = mul(sub(1, pb), inv(pb));
    return add(m, k, mean);
  }
  if (d[n][m] != -1) {
    return d[n][m];
  }
  int& res = d[n][m];
  res = add(mul(pa, calc(n + 1, m)), mul(pb, calc(n, n + m)));
  return res;
}

signed main() {
#ifdef LOCAL
  assert(freopen("test.in", "r", stdin));
#endif
  cin >> k >> pa >> pb;
  memset(d, -1, sizeof(d));
  for (int i = 0; i < maxn; ++i) {
    for (int j = 0; j < maxn; ++j) {
      d[i][j] = -1;
    }
  }
  int isum = inv(pa + pb);
  uul(pa, isum);
  uul(pb, isum);
  cout << calc(1, 0) << '\n';
}