#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL n, p, a, b, phi;

struct mat
{
	LL v[2][2];
	
	mat() {
		memset(v, 0, sizeof(v));
	}
	mat(int i, int j, int k, int l) {
		v[0][0] = i, v[0][1] = j,
		v[1][0] = k, v[1][1] = l;
	}
};

mat operator *(const mat &a, const mat &b)
{
	mat c;
	for (int i=0; i<2; ++i) {
		for (int j=0; j<2; ++j) {
			for (int k=0; k<2; ++k) {
				c.v[i][j] += a.v[i][k]*b.v[k][j];
			} 
			if (c.v[i][j]>=phi) 
				c.v[i][j]=c.v[i][j]%phi+phi;
		}
	}
	return c;
}

LL fpow(LL a, LL b, LL mod)
{
	LL ans = 1, base = a%mod;
	while (b) {
		if (b&1) ans *= base, ans %= mod;
		base *= base, base %= mod;
		b >>= 1;
	}
	return ans;
}

mat fpow(const mat &a, LL b, LL mod)
{
	mat ans(1, 0, 0, 1), base = a; 
	while (b) {
		if (b&1) ans = ans*base;
		base = base*base; 
		b >>= 1;
	}
	return ans;
}

LL euler(int n)
{
	LL ans = n;
	for (int i=2; i*i<=n; ++i) {
		if (n%i == 0) {
			ans = ans*(i-1)/i;
			while (n%i == 0) n /= i;
		}
	}
	if (n>1) ans = ans*(n-1)/n;
	return ans;
}

LL solve()
{
	phi = euler(p);
	mat vec(0, 1, 1, 1); vec = fpow(vec, n-1, p);
	mat frac = mat(1, 0, 0, 0)*vec;
	return fpow(a, frac.v[0][0], p)*fpow(b, frac.v[0][1], p)%p;
}

int main()
{
	int t; scanf("%d", &t);
	for (int kase=1; kase<=t; ++kase)
	{
		scanf("%lld%lld%lld%lld", &a, &b, &p, &n);
		printf("Case #%d: %lld\n", kase, solve());
	}
}
