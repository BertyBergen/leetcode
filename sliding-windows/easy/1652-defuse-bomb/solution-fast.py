from typing import List

class Solution:
    def decrypt(self, code: List[int], k: int) -> List[int]:
        n = len(code)
        if k == 0:
            return [0] * n

        res = [0] * n

        if k > 0:
            # i = 0: сумма следующих k элементов -> индексы 1..k
            window_sum = sum(code[1:1 + k])
            res[0] = window_sum
            for i in range(1, n):
                out_idx = i                  # уходит элемент code[i]
                in_idx = (i + k) % n         # заходит элемент справа
                window_sum += -code[out_idx] + code[in_idx]
                res[i] = window_sum
            return res

        # k < 0: суммируем предыдущие |k| элементов
        k = -k  # теперь это "сколько предыдущих"
        # i = 0: предыдущие k -> индексы n-k..n-1
        window_sum = sum(code[n - k:])
        res[0] = window_sum
        for i in range(1, n):
            # Переход от S_{i-1} к S_i:
            # выкидываем самый дальний прошлый: (i - k - 1)
            # добавляем ближайший прошлый: (i - 1)
            out_idx = (i - k - 1) % n
            in_idx  = (i - 1) % n
            window_sum += -code[out_idx] + code[in_idx]
            res[i] = window_sum

        return res
