class Solution:
    def targetIndices(self, nums: List[int], target: int) -> List[int]:
        n = len(nums)
        nums.sort()
        left, right = 0, n

        while left < right:
            mid = (right + left)//2

            if nums[mid] < target:
                left = mid + 1
            else:
                right = mid
        
        starts = left
        left, right = 0, n

        while left < right:
            mid = (right + left)//2

            if nums[mid] <= target:
                left = mid + 1
            else:
                right = mid
        ends = left
        if starts is None:
            return []
        return list(range(starts, ends))