from collections import deque
from typing import List

class Solution:
    def countNonDecreasingSubarrays(self, nums: List[int], k: int) -> int:
        reversed_nums = nums[::-1]
        q = deque()
        result = 0
        left = 0
        remain = k

        for right, value in enumerate(reversed_nums):
            
            while q and reversed_nums[q[-1]] <  value:
                rm_idx = q.pop()
                prev_idx = q[-1] if q else left - 1
                remain -= (rm_idx - prev_idx)*(value - reversed_nums[rm_idx])
            
            q.append(right)
            
            while remain < 0:
                remain += reversed_nums[q[0]] - reversed_nums[left]
                
                if q[0] == left:
                    q.popleft()
                left += 1

            result += right - left + 1
        return result


jopa = Solution()
arr = [8,1,4,5,7,5,6,7,8,8]
arr2 = [3,1,4]


print('total subarrays', jopa.countNonDecreasingSubarrays(arr, 10))