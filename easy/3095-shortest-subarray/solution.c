int minimumSubarrayLength(int* nums, int numsSize, int k) {
    int minLen = numsSize + 1;
    int l = 0, r = 0;
    int n = 0;

    while (r < numsSize) {
        n |= nums[r];
        r++;

        if (n >= k) {
            if (r - l < minLen) minLen = r - l;
            n = 0;
            l++;
            r = l;
        }
    }

    return (minLen == numsSize + 1) ? -1 : minLen;
}


int main() {
    int nums[] = {1, 2, 3, 4};
    int k = 7;
    int size = sizeof(nums) / sizeof(nums[0]);

    int res = minimumSubarrayLength(nums, size, k);
    printf("%d\n", res); // вывод: 3

    return 0;
}


