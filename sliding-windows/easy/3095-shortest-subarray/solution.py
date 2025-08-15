class Solution:
    def minimumSubarrayLength(self, nums: List[int], k: int) -> int:
        result = []
        
        left, right = 0, 0
        n = 0
        
        while right < len(nums):
            n |= nums[right]
            right += 1

            if n >= k:
                result.append(right - left)
                n = 0
                left += 1
                right = left

        return min(result) if result else -1