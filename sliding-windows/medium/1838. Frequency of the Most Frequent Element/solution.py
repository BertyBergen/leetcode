from typing import List

class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        nums.sort()
        n = len(nums)
        left = 0

        for right in range(n):
            k -= nums[right] - nums[(right + left) // 2]
            
            if k < 0:
                k += nums[(right + left + 1)//2] -  nums[left] 
                left += 1 
        return n - left

        

arr = [5,5,5,5,5,5,11,19,20]
arr2 = [[1,2,4]]

sol = Solution()
print(sol.maxFrequency(arr2, 0))