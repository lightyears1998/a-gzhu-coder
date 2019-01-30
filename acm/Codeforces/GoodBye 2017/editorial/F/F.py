n = int(raw_input())

ans = 0
allc = 0
bigr = 0
bigb = 0
lastr = -1
lastb = -1
lastg = -(1<<60)

for i in range(n):
	x = raw_input().split()
	pos, col = int(x[0]), x[1]

	if col == 'R' or col == 'G':
		if lastr != -1:
			bigr = max(bigr, pos - lastr)
			allc += pos - lastr
		lastr = pos
	if col == 'B' or col == 'G':
		if lastb != -1:
			bigb = max(bigb, pos - lastb)
			allc += pos - lastb
		lastb = pos

	if col == 'G':
		ans += allc + min(0, - bigr - bigb + pos - lastg)
		lastr = lastb = lastg = pos
		bigr = bigb = allc = 0

ans += allc

print ans