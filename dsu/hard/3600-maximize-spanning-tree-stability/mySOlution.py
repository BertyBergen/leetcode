from typing import List

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))

    def find(self, x):
        while self.parent[x] != x:
            self.parent[x] = self.parent[self.parent[x]]
            x = self.parent[x]
        return x

    def union(self, x, y):
        xr, yr = self.find(x), self.find(y)
        if xr == yr:
            return False
        self.parent[yr] = xr
        return True

class Solution:
    def maxStability(self, n: int, edges: List[List[int]], k: int) -> int:
        def can_build(stability):
            dsu = DSU(n)
            count = 0
            used_upgrades = 0
            
            for u, v, strength, must in edges:
                if must == 1:
                    if strength < stability:
                        return False  
                    if dsu.union(u, v):
                        count += 1
            
            optional_edges = []
            for u, v, strength, must in edges:
                if must == 0:
                    if strength >= stability:
                        optional_edges.append((0, u, v))  
                    elif strength * 2 >= stability:
                        optional_edges.append((1, u, v))  

            optional_edges.sort()

            for need_upgrade, u, v in optional_edges:
                if need_upgrade == 1 and used_upgrades >= k:
                    continue
                if dsu.union(u, v):
                    count += 1
                    if need_upgrade == 1:
                        used_upgrades += 1
                if count == n - 1:
                    return True
            return False

        low, high = 0, max(strength * 2 for _, _, strength, _ in edges)
        result = -1

        while low <= high:
            mid = (low + high) // 2
            if can_build(mid):
                result = mid
                low = mid + 1  
            else:
                high = mid - 1

        return result
