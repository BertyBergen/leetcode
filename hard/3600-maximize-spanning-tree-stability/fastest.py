class UF:
    def __init__(self, n):
        self.id = list(range(n))

    def union(self, u, v):
        u = self.find(u)
        v = self.find(v)
        if u == v:
            return False
        self.id[u] = v
        return True

    def find(self, up):
        while (up:=self.id[up]) != (deep:=self.id[up]):
            self.id[up] = self.id[deep]
        return up

class Solution:
    def maxStability(self, n: int, edges: List[List[int]], k: int) -> int:
        uf = UF(n)
        min_s = inf
        cou = n-1
        remain = []
        for n1,n2, s, must in edges :
            if must :
                if not uf.union(n1, n2) :
                    return -1
                if s < min_s :
                    min_s = s
                cou -= 1
            else :
                remain.append( (n1,n2,s) )
        if cou == 0 :
            return min_s
        
        remain.sort(reverse = True, key = lambda x : x[2])
        for n1,n2, s in remain :
            if uf.union(n1, n2) :
                if cou <= k :
                    min_s = min(min_s, s*2)
                else :
                    min_s = min(min_s, s)
                cou -= 1
                if cou == 0 :
                    return min_s
        if cou == 0 :
            return min_s
        else :
            return -1