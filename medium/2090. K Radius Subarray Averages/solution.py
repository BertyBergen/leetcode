class Solution:
    def getAverages(self, nums: List[int], k: int) -> List[int]:
        result = []
        window = k*2 + 1
        result = [-1] * len(nums)
        
        if window > len(nums):    
            return result
        sum__ = 0

        for i in range(len(nums)):
            sum__ += nums[i]
            if i >= window:
                sum__ -= nums[i - window]
            if i >= window - 1:
                result[i - k] = sum__//window

        return result

class Solution:
    def getAverages(self, nums: List[int], k: int) -> List[int]:
        length_ = len(nums)
        window = 2*k+1
        result = [-1]*length_

        ## Edge cases
        if k==0:
            return nums
        if length_<window:
            return result
        
        # Sum over first window
        sum_ = sum(nums[:window])
        result[k] = sum_//window

        for i in range(window,length_):
            sum_ = sum_ - nums[i-window] + nums[i]
            result[i-k] = sum_//window

        return result
    