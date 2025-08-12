#define VALUE_SIZE  100001

int maxFrequency(int* nums, int numsSize, int k) {
    int anCount[VALUE_SIZE];
    memset(anCount, 0, VALUE_SIZE*sizeof(int));

    // count input *nums into hashtable
    int nMin = VALUE_SIZE, nMax = 0;
    while(numsSize--)
    {
        if(nMin > *nums) nMin = *nums;
        if(nMax < *nums) nMax = *nums;

        anCount[*(nums++)]++;
    }

    // using sliding window, trace from nMax to nMin
    int nCurrValue = nMax - 1, nRet = 0, nTmp = anCount[nMax];
    while(nMin <= nCurrValue)
    {
        // check if we have value nCurrValue
        if(anCount[nCurrValue])
        {
            int nDiff = nMax - nCurrValue, nCount = k / nDiff;
            if(nCount < anCount[nCurrValue])
            {
                // input k is not enough for nCurrValue, just only count nCount
                // update nRet if we have larger nSum
                int nSum = nTmp + nCount;
                if(nRet < nSum) nRet = nSum;

                // trace to find next nMax and restore k
                nTmp -= anCount[nMax--];
                k += nTmp;
                while(nCurrValue < nMax && 0 == anCount[nMax])
                {
                    nMax--;
                    k += nTmp;
                }

                // update nTmp directly if nMax is equal to nCurrValue
                if(nCurrValue == nMax)
                {
                    nTmp = anCount[nMax];
                }
                else
                {
                    // ** we need to add nCurrValue back to recheck current value again in next round
                    nCurrValue++;
                }
            }
            else
            {
                // input k is still enough for nCurrValue, just add into nTmp
                nTmp += anCount[nCurrValue];
                k -= nDiff * anCount[nCurrValue];
            }
        }

        nCurrValue--;
    }

    // update nRet if we have larger nTmp
    if(nRet < nTmp) nRet = nTmp;

    return nRet;
}