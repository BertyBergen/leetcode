class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        right, left = len(nums) - 1, 0

        while left <= right:
            mid = (right + left) // 2
            if nums[mid] == target:
                return mid
            
            elif nums[mid] < target:
                left = mid + 1
            else: 
                right = mid - 1
        return left