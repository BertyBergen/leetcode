#include <stdlib.h>

int* getAverages(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = numsSize;
    int* ans = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; ++i) ans[i] = -1; 

    int window = 2 * k + 1;
    if (window > numsSize) return ans; 

    long long sum = 0;
    for (int i = 0; i < numsSize; ++i) {
        sum += nums[i];

        if (i >= window) sum -= nums[i - window]; 

        if (i >= window - 1) ans[i - k] = (int)(sum / window);
    }

    return ans;
}
