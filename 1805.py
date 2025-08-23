import re
class Solution:
    def numDifferentIntegers(self, word: str) -> int:
        nums = re.findall(r'\d+', word)
        nums = [num.lstrip('0') or '0' for num in nums]
        return len(set(nums))