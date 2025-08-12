#include <stdio.h>
#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int maxFrequency(int* nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), cmp_int);

    long long sum = 0;
    int left = 0;
    int res = 0;

    for (int right = 0; right < numsSize; right++) {
        sum += nums[right];

        while ((long long)nums[right] * (right - left + 1) - sum > k) {
            sum -= nums[left];
            left++;
        }

        if (right - left + 1 > res)
            res = right - left + 1;
    }

    return res;
}

int main() {
    int nums[] = {1, 4, 8, 13};
    int size = sizeof(nums) / sizeof(nums[0]);
    int k = 5;

    printf("%d\n", maxFrequency(nums, size, k)); 
    return 0;
}
