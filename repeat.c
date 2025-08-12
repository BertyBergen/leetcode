#include <stdio.h>
#include <stdlib.h>

int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}


int maxFrequency(int* nums, int numsSize, int k) {
        
}

int main()
{
    int nums[] = {1, 4, 8, 13};
    int size = sizeof(nums) / sizeof(nums[0]);
    int k = 5;

    printf("%d\n", maxFrequency(nums, size, k)); 
    
    return 0;
}