from itertools import accumulate

class Solution:
    def minimumSumSubarray(self, nums: List[int], l: int, r: int) -> int:
        n = len(nums)
        prefix_sum = list(accumulate(nums, initial=0))
        result = inf
        
        for left in range(n-l+1):
            for right in range(left+l, min(left+r+1, n+1)):
                total = prefix_sum[right]-prefix_sum[left]
                if total<result and total>0:
                    result = total

        return result if result!=inf else -1