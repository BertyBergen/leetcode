#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getAverages(int* nums, int numsSize, int k, int* returnSize) {

    *returnSize = numsSize;
    int* avgs = (int*)malloc(sizeof(int) * numsSize);
    
    if (k == 0) {
        memcpy((void*)avgs, (void*)nums, (sizeof(int) * numsSize));   
    } else if (numsSize < (k * 2 + 1)) {
        memset((void*)avgs, 0xFF, (sizeof(int) * numsSize));   
    } else {
        memset((void*)avgs, 0xFF, (sizeof(int) * k)); 
        memset((void*)(avgs + (numsSize - k)), 0xFF, (sizeof(int) * k)); 
        
        unsigned long int cnt = (unsigned long int)k * 2 + 1, sum = (unsigned long int)nums[0];
        
        for (int i = 1; i < k * 2; ++i) {
            sum += (unsigned long int)nums[i];
        }
        
        for (int i = k; i < (numsSize - k); ++i) {
            sum += (unsigned long int)nums[i + k];
            avgs[i] = (int)(sum / cnt);
            sum -= (unsigned long int)nums[i - k];
        }
    }
    
    return avgs;
}