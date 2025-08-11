def maxFrequencyScore(nums, k):
    nums.sort()
    n = len(nums)
    pref = [0] * n
    pref[0] = nums[0]
    for i in range(1, n):
        pref[i] = pref[i-1] + nums[i]

    def sum_range(L, R):
        if L > R:
            return 0
        return pref[R] - (pref[L-1] if L > 0 else 0)

    left = 0
    max_len = 1

    for right in range(n):
        while left <= right:
            length = right - left + 1
            mid = left + (length - 1) // 2
            median = nums[mid]

            sumL = sum_range(left, mid)
            sumR = sum_range(mid + 1, right)

            left_count = mid - left + 1
            right_count = right - mid

            cost = median * left_count - sumL + sumR - median * right_count

            if cost <= k:
                break
            left += 1

        cur_len = right - left + 1
        if cur_len > max_len:
            max_len = cur_len

    return max_len

# Пример
nums = [1, 2, 6, 4]
k = 3
print(maxFrequencyScore(nums, k))  # Выведет 3
