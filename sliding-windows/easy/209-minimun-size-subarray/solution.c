int minSubArrayLen(int target, int* nums, int numsSize) 
{
    int min = INT_MAX;
    int sum = 0;
    int left = 0;

    for (int right = 0; right < numsSize; ++right)
    {
        sum += nums[right];
        
        while (sum >= target)
        {
            if (min > right - left +1) min = right - left +1;
            sum -= nums[left];
            left++;
        }
            
    }
    return min == INT_MAX ? 0 : min;
}