double findMaxAverage(int* nums, int numsSize, int k) {
    double sum = 0;
    int counter = k - 1; // counter = 3
    if(numsSize == 1) return nums[0];
    for(int i = 0; i < k; i++){
        sum += nums[i];
    }
    double max = sum;
    int j = 1;
    while(counter < numsSize){ // counter = 3
        counter = counter + 1; // 1. counter = 4
        if(counter >= numsSize) break;
        sum = sum + nums[counter];
        sum = sum - nums[j - 1];
        if(sum > max) max = sum;
        j++;
    }
    return (max / k);
}