#include <stdlib.h>

long long countNonDecreasingSubarrays(int* nums, int numsSize, int maxOps) {
    long long remainingOps = maxOps; 

    // Переворачиваем массив, чтобы идти справа налево
    int* reversed = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++)
        reversed[i] = nums[numsSize - 1 - i];

    // Монотонная очередь для индексов «важных элементов»
    int* q = (int*)malloc(numsSize * sizeof(int));
    int qstart = 0, qend = 0;

    int left = 0;       // левый конец окна
    long long totalSubarrays = 0;

    for (int right = 0; right < numsSize; right++) {
        // Убираем из очереди элементы, которые меньше текущего
        while (qend > qstart && reversed[q[qend - 1]] < reversed[right]) {
            int removedIdx = q[--qend];
            int prevIdx = (qend > qstart) ? q[qend - 1] : left - 1;
            // Считаем стоимость поднятия элементов до нового максимума
            remainingOps -= (long long)(removedIdx - prevIdx) * (reversed[right] - reversed[removedIdx]);
        }

        // Добавляем текущий индекс в очередь
        q[qend++] = right;

        // Если превысили лимит операций, сдвигаем левый конец окна
        while (remainingOps < 0) {
            remainingOps += (long long)(reversed[q[qstart]] - reversed[left]);
            if (q[qstart] == left) qstart++;
            left++;
        }

        // Добавляем количество валидных подмассивов с правым концом right
        totalSubarrays += right - left + 1;
    }

    free(reversed);
    free(q);
    return totalSubarrays;
}
