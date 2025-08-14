int minimumSumSubarray(int* nums, int numsSize, int l, int r) {
    int minSum = INT_MAX;

    for (int start = 0; start < numsSize; start++) {
        int sum = 0;
        for (int end = start; end < numsSize && end - start + 1 <= r; end++) {
            sum += nums[end];

            int length = end - start + 1;
            if (length >= l && sum > 0 && sum < minSum) {
                minSum = sum;
            }
        }
    }

    return minSum == INT_MAX ? -1 : minSum;
}