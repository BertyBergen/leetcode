#include <stdlib.h>

long long countNonDecreasingSubarrays(int* nums, int numsSize, int maxOps) {
    long long remain = maxOps; 

    // Переворачиваем массив, чтобы идти справа налево
    int* reversed = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++)
        reversed[i] = nums[numsSize - 1 - i];

    // Монотонная очередь для индексов «важных элементов»
    int* q = (int*)malloc(numsSize * sizeof(int));

    int left = 0;       // левый конец окна
    long long result = 0;

    for (int right = 0; right < numsSize; right++) {
        // Убираем из очереди элементы, которые меньше текущего
        while (right > left && reversed[q[right - 1]] < reversed[right]) {
            int rmIdx = q[--right];
            int prevIdx = (right > left) ? q[right - 1] : left - 1;
            // Считаем стоимость поднятия элементов до нового максимума
            remain -= (long long)(rmIdx - prevIdx) * (reversed[right] - reversed[rmIdx]);
        }

        // Добавляем текущий индекс в очередь
        q[right++] = right;

        // Если превысили лимит операций, сдвигаем левый конец окна
        while (remain < 0) {
            remain += (long long)(reversed[q[left]] - reversed[left]);
            if (q[left] == left) left++;
            left++;
        }

        // Добавляем количество валидных подмассивов с правым концом right
        result += right - left + 1;
    }

    free(reversed);
    free(q);
    return result;
}
