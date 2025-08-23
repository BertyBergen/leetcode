from typing import List

class Solution:
    def search(self, nums: List[int], target: int) -> int:
        n = len(nums)
        left, right = 0, n

        while left < right:
        
            mid = (right + left)//2
            
            if nums[mid] == target:
                print("MID", mid)
                return mid
            
            elif nums[mid] < target:
                left = mid + 1
                print("left",left)
            
            else:
                right = mid  
                print("Right", right)     
        return -1 
    
sol = Solution()
arr = [1,2,3,4,6,7,8,12]

print(sol.search(arr,1))