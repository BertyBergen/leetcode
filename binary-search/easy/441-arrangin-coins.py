class Solution:
    def arrangeCoins(self, n: int) -> int:
        left, right = 0, n
        while left <= right:
            mid = (left + right) // 2
            s = mid*(mid + 1)//2
            if s == n: 
                return mid
            if s < n:
                left = mid + 1
            else:
                right = mid - 1
        return right
