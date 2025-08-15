

double findMaxAverage(int* nums, int numsSize, int k) 
{
    int sum = 0;
    for (int i = 0; i < k; ++i)
    {
        sum += nums[i]; 
    }
    int maxsum = sum;
    for (int i = k; i < numsSize; ++i)
    {
        int newsum = sum - nums[i - k] + nums[i];
        sum = newsum;
        if (maxsum < newsum) maxsum = newsum;
    }

    return (double)maxsum/k;
}