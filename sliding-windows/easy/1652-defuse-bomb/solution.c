#include <stdlib.h>

int* decrypt(int* code, int codeSize, int k, int* returnSize) {
    int n = codeSize;
    int* ans = (int*)malloc(n * sizeof(int));
    *returnSize = n;

    for (int i = 0; i < n; i++)
        ans[i] = 0;

    if (k == 0) return ans;

    if (k > 0) {
        int wsum = 0;
        for (int j = 1; j <= k; j++)
            wsum += code[j % n];
        ans[0] = wsum;

        for (int i = 1; i < n; i++) {
            int r = (i + k) % n;
            wsum += code[r] - code[i];
            ans[i] = wsum;
        }
    } else { // k < 0
        int wsum = 0;
        for (int j = 1; j <= -k; j++)
            wsum += code[(n - j) % n];
        ans[0] = wsum;

        for (int i = 1; i < n; i++) {
            int r = (i - k + n) % n;
            wsum += code[(n - r + n) % n] - code[(n - i + n) % n];
            ans[(n - i) % n] = wsum;
        }
    }

    return ans;
}
