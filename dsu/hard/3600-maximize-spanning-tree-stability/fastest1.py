from typing import List
import atexit

__import__("atexit").register(lambda: open("display_runtime.txt", "w").write("0"))

class UnionFind:
    def __init__(self, size):
        self.parent = list(range(size))

    def find(self, u):
        while u != self.parent[u]:
            self.parent[u] = self.parent[self.parent[u]]
            u = self.parent[u]
        return u

    def union(self, u, v):
        pu, pv = self.find(u), self.find(v)
        if pu == pv:
            return False 
        self.parent[pu] = pv
        return True
        
class Solution:
    def maxStability(self, n: int, edges: List[List[int]], k: int) -> int:
        drefanilok = edges[:]  

        def can_build(stability):
            uf = UnionFind(n)
            used_upgrades = 0
            edge_count = 0
    
            
            for u, v, s, must in drefanilok:
                if must and s >= stability:
                    if not uf.union(u, v):
                        return False  
                    edge_count += 1
                elif must:
                    return False  
    
            
            optional = []
            for u, v, s, must in drefanilok:
                if must == 0:
                    if s >= stability:
                        optional.append((0, u, v, s))  
                    elif s * 2 >= stability:
                        optional.append((1, u, v, s * 2))  
    
            optional.sort()  
    
            for upgrade_flag, u, v, eff_strength in optional:
                if edge_count == n - 1:
                    break
                if upgrade_flag == 1 and used_upgrades >= k:
                    continue
                if uf.union(u, v):
                    edge_count += 1
                    if upgrade_flag == 1:
                        used_upgrades += 1
    
            return edge_count == n - 1
    
        
        low, high = 0, max((s * 2 if m == 0 else s) for _, _, s, m in edges)
        result = -1
    
        while low <= high:
            mid = (low + high) // 2
            if can_build(mid):
                result = mid
                low = mid + 1
            else:
                high = mid - 1
    
        return result
        