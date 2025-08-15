from collections import deque
from typing import List

class Solution:
    def countNonDecreasingSubarrays(self, nums: List[int], k: int) -> int:
        # Переворачиваем массив, чтобы идти справа налево
        reversed_nums = nums[::-1]
        
        total_subarrays = 0           # Результат — количество валидных подмассивов
        mono_queue = deque()          # Монотонная очередь, хранит индексы важных элементов
        window_start = 0              # Левый конец окна

        remaining_ops = k             # Сколько операций ещё можно использовать

        for window_end, value in enumerate(reversed_nums):
            # Убираем из очереди элементы, которые меньше текущего
            while mono_queue and reversed_nums[mono_queue[-1]] < value:
                removed_idx = mono_queue.pop()
                prev_idx = mono_queue[-1] if mono_queue else window_start - 1
                remaining_ops -= (removed_idx - prev_idx) * (value - reversed_nums[removed_idx])

            # Добавляем текущий индекс в очередь
            mono_queue.append(window_end)

            # Если операций не хватает, сдвигаем левый конец окна
            while remaining_ops < 0:
                remaining_ops += reversed_nums[mono_queue[0]] - reversed_nums[window_start]
                if mono_queue[0] == window_start:
                    mono_queue.popleft()
                window_start += 1

            # Добавляем количество валидных подмассивов с правым концом window_end
            total_subarrays += window_end - window_start + 1

        return total_subarrays
