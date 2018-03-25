from itertools import permutations

n,m = map(int, raw_input().split())

g = [raw_input() for __ in range(n)]

inst = map(int, raw_input())

dx = [0,-1,0,1]
dy = [1,0,-1,0]

sx, sy, ex, ey = -1, -1, -1, -1
for i in range(n):
    for j in range(m):
        if g[i][j] == 'S':
            sx,sy = i,j
        if g[i][j] == 'E':
            ex,ey = i,j

def go(dirs):
    cx,cy = sx,sy
    for e in inst:
        cx += dx[dirs[e]]
        cy += dy[dirs[e]]

        if not (0 <= cx < n and 0 <= cy < m and g[cx][cy] != '#'):
            return False

        if (cx,cy) == (ex,ey):
            return True
    return False

print sum(map(go, permutations(range(4))))