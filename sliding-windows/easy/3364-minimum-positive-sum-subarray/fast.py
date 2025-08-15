from typing import List

class Solution:
    def minimumSumSubarray(self, nums: List[int], l: int, r: int) -> int:
        n = len(nums)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i+1] = prefix[i] + nums[i]
        
        min_sum = float('inf')
        for start in range(n):
            for end in range(start + l, min(n, start + r) + 1):
                s = prefix[end] - prefix[start]
                if s > 0:
                    min_sum = min(min_sum, s)

        return min_sum if min_sum != float('inf') else -1
