class Solution:
    def isPerfectSquare(self, num: int) -> bool:
        if num < 2:
            return True
        
        left, right = 0, num //2

        while left <= right:

            mid = left + (right - left)//2
            
            square = mid*mid

            if square < num:
                left = mid + 1
            elif square > num:
                right = mid - 1
            else:
                return True
        return False

def isPerfectSquare(num: int) -> bool:
    if num < 2:
        return True
    
    x = num // 2  # начальное приближение
    while x * x > num:
        x = (x + num // x) // 2  # формула Ньютона
    
    return x * x == num