class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def unite(self, x, y):
        fx, fy = self.find(x), self.find(y)
        if fx == fy:
            return False
        self.parent[fy] = fx
        return True

def maximizeStability(n, k, edges):
    def canBuild(minStability):
        dsu = DSU(n)
        upgrades = 0
        count = 0

        for u, v, s, must in edges:
            if must and s < minStability:
                return False
            if must and dsu.unite(u, v):
                count += 1

        for u, v, s, must in edges:
            if must:
                continue
            if s >= minStability and dsu.unite(u, v):
                count += 1
            elif s * 2 >= minStability and upgrades < k and dsu.unite(u, v):
                upgrades += 1
                count += 1

        return count == n - 1

    edges.sort(key=lambda x: -x[2])
    low, high = 0, 10**9 + 1
    ans = -1

    while low <= high:
        mid = (low + high) // 2
        if canBuild(mid):
            ans = mid
            low = mid + 1
        else:
            high = mid - 1
    return ans
