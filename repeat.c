int minimumSumSubarray(int* nums, int numsSize, int l, int r)
{
    int min = INT_MAX;

    for (int i = 0; i < numsSize; ++i)
    {
        int sum = 0;
        
        for (int j = i; j < i + r &&  j < numsSize; ++j)
        {
            sum += nums[j];

            int length = j - i + 1;
            if (length >= l && sum > 0 && sum < min) min = sum;
        }
    }
    return min == INT_MAX ? -1 : min;
}