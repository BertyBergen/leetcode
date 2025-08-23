class Solution:
    def decrypt(self, code: List[int], k: int) -> List[int]:
        n=len(code)
        ans=[0]*n
        if k==0: return ans
        if k>0:
            ans[0]=wsum=sum(code[1:k+1])
            for i in range(n):
                r=(i+k)%n
                wsum+=code[r]-code[i]
                ans[i]=wsum
            return ans
        ans[0]=wsum=sum(code[-1:k-1:-1])
        for i in range(1,n):
            r=(i-k)%n
            wsum+=code[-r]-code[-i]
            ans[-i]=wsum
        return ans