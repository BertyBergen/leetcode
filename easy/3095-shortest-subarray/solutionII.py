from typing import List

class Solution:
    def minimumSubarrayLength(self, nums: List[int], k: int) -> int:
        n = len(nums)
        min_len = float(n + 1)

        for left in range(n):
            or_val = 0
            for right in range(left, n):
                or_val |= nums[right]
                if or_val >= k:
                    min_len = min(min_len, right - left + 1)
                    break  # дальше будет только длиннее
        return min_len if min_len != float('inf') else -1
