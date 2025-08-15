class Solution:
    def longestNiceSubstring(self, s: str) -> str:
        if len(s) < 2:
            return ""

        letters = set(s)

        for c in letters:
            if c.swapcase() not in letters:
                parts = s.split(c)
                longest = ""
                for part in parts:
                    candidate = self.longestNiceSubstring(part)
                    if len(candidate) > len(longest):
                        longest = candidate
                return longest

        return s

