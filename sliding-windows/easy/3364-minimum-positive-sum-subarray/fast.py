from typing import List

class Solution:
    def minimumSumSubarray(self, nums: List[int], l: int, r: int) -> int:
        n = len(nums)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i+1] = prefix[i] + nums[i]
        
        min_sum = float('inf')
        for left in range(n):
            for right in range(left + l, min(n, left + r) + 1):
                s = prefix[right] - prefix[left]
                if s > 0:
                    min_sum = min(min_sum, s)

        return min_sum if min_sum != float('inf') else -1
