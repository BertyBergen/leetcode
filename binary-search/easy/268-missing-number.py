class Solution:
    def missingNumber(self, nums: List[int]) -> int:
        n = len(nums)
        left, right = 0, n
        s = n*(n + 1)//2
        return s - sum(nums)
    
class Solution:
    def missingNumber(self, nums: list[int]) -> int:
        n = len(nums)
        xor_all = 0
        for i in range(n + 1):
            xor_all ^= i
        xor_nums = 0
        for num in nums:
            xor_nums ^= num
        return xor_all ^ xor_nums


class Solution:
    def missingNumber(self, nums: list[int]) -> int:
        nums.sort()
        left, right = 0, len(nums) - 1
        
        while left <= right:
            mid = (left + right) // 2
            if nums[mid] == mid:
                left = mid + 1
            else:
                right = mid - 1
        
        return left
