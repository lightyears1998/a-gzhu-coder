from collections import defaultdict

mod = 1000000007

comb = [[1]]
for i in range(1,1010):
	x = [1]
	for j in range(1,i):
		x.append((comb[i-1][j-1]+comb[i-1][j]) % mod)
	x.append(1)
	comb.append(x)

dp = [1]
for i in range(1,1010):
	r = 0
	for k in range(i):
		r += dp[k] * comb[i-1][k]
		r %= mod
	dp.append(r)

m,n = map(int, raw_input().split())

ns = [0 for __ in range(m)]
for j in range(n):
	s = map(int, raw_input())
	for i in range(m):
		ns[i] |= s[i] << j

dd = defaultdict(int)
for e in ns:
	dd[e] += 1

ans = 1
for b in dd.values():
	ans = ans * dp[b] % mod

print ans