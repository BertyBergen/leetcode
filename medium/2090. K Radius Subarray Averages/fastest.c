/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getAverages(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = numsSize;
    int *result = malloc(numsSize * sizeof(int)); 

    int windowSize = 2*k + 1;
    
    if (k == 0) 
    {
        memcpy((void *)result, (void *)nums, sizeof(int) * numsSize);
        return result;
    }
    
    else if (windowSize > numsSize)
    {
        memset((void*)result,0xFF, sizeof(int) *  numsSize);
        return result;
    } 
    else
    {

        memset(result, 0xFF,k * sizeof(int));
        memset((result + (numsSize - k)), 0xFF,(k * sizeof(int)));
        
        unsigned long long sum = 0;

        for (int i = 0; i < numsSize; i++)
        {
            sum += nums[i];
            if (i >= windowSize) sum -= nums[i - windowSize];
            if (i >= windowSize - 1) result[i - k] = (int)(sum/windowSize); 

        }
    }
    
    return result;


}