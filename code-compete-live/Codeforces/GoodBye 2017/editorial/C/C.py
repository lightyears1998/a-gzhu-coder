import math
n,r = map(int, raw_input().split())
x = map(int, raw_input().split())

y = []
for i in range(n):
    y.append(
        max([r] + [math.sqrt(4 * r * r - (x[i]-x[j])*(x[i]-x[j])) + y[j]
        for j in range(i) if abs(x[i]-x[j]) <= 2 * r])
    )
print " ".join(map(str,y))