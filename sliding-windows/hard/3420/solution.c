#include <stdlib.h>

long long countNonDecreasingSubarrays(int* nums, int numsSize, int maxOps) {
    long long remainingOps = maxOps; 

    // Переворачиваем массив, чтобы идти справа налево
    int* reversed = (int*)malloc(numsSize * sizeof(int));
    for (int idx = 0; idx < numsSize; idx++)
        reversed[idx] = nums[numsSize - 1 - idx];

    // Монотонная очередь для индексов «важных элементов»
    int* monoQueue = (int*)malloc(numsSize * sizeof(int));
    int queueStart = 0, queueEnd = 0;

    int windowStart = 0;       // левый конец окна
    long long totalSubarrays = 0;

    for (int windowEnd = 0; windowEnd < numsSize; windowEnd++) {
        // Убираем из очереди элементы, которые меньше текущего
        while (queueEnd > queueStart && reversed[monoQueue[queueEnd - 1]] < reversed[windowEnd]) {
            int removedIdx = monoQueue[--queueEnd];
            int prevIdx = (queueEnd > queueStart) ? monoQueue[queueEnd - 1] : windowStart - 1;
            // Считаем стоимость поднятия элементов до нового максимума
            remainingOps -= (long long)(removedIdx - prevIdx) * (reversed[windowEnd] - reversed[removedIdx]);
        }

        // Добавляем текущий индекс в очередь
        monoQueue[queueEnd++] = windowEnd;

        // Если превысили лимит операций, сдвигаем левый конец окна
        while (remainingOps < 0) {
            remainingOps += (long long)(reversed[monoQueue[queueStart]] - reversed[windowStart]);
            if (monoQueue[queueStart] == windowStart) queueStart++;
            windowStart++;
        }

        // Добавляем количество валидных подмассивов с правым концом windowEnd
        totalSubarrays += windowEnd - windowStart + 1;
    }

    free(reversed);
    free(monoQueue);
    return totalSubarrays;
}
