from typing import List

class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        def my_bisect_left(arr, x):
            left, right = 0, len(arr)
            while left < right:
                mid = (left + right) // 2
                if arr[mid] < x:
                    left = mid + 1
                else:
                    right = mid
            return left  
        
        sub = []
        for x in nums:
            i = my_bisect_left(sub, x)
            if i == len(sub):
                sub.append(x)
            else:
                sub[i] = x
        return len(sub)


