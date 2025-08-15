#include <stdlib.h>

long long countNonDecreasingSubarrays(int* nums, int numsSize, int k) {
    long long K = k; 
    int* A = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++)
        A[i] = nums[numsSize - 1 - i];

    int* q = (int*)malloc(numsSize * sizeof(int));
    int front = 0, back = 0;
    int i = 0;
    long long res = 0;

    for (int j = 0; j < numsSize; j++) {
        while (back > front && A[q[back - 1]] < A[j]) {
            int r = q[--back];
            int l = (back > front) ? q[back - 1] : i - 1;
            K -= (long long)(r - l) * (A[j] - A[r]); // приведение к long long
        }
        q[back++] = j;

        while (K < 0) {
            K += (long long)(A[q[front]] - A[i]);
            if (q[front] == i) front++;
            i++;
        }

        res += j - i + 1;
    }

    free(A);
    free(q);
    return res;
}
