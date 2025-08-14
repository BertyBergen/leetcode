#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

typedef struct {
    int n;
    int *bit;
} Fenwick;

Fenwick fenw_create(int n) {
    Fenwick f;
    f.n = n;
    f.bit = (int*)calloc(n + 1, sizeof(int));
    return f;
}
void fenw_add(Fenwick *f, int idx, int delta) 
{ 
    for (; idx <= f->n; idx += idx & -idx) f->bit[idx] += delta;
}
int fenw_sum(Fenwick *f, int idx) { // sum [1..idx]
    int s = 0;
    for (; idx > 0; idx -= idx & -idx) s += f->bit[idx];
    return s;
}
int fenw_find_by_order(Fenwick *f, int k) {
    int idx = 0;
    int bitmask = 1 << (31 - __builtin_clz(f->n)); 
    for (; bitmask; bitmask >>= 1) {
        int next = idx + bitmask;
        if (next <= f->n && f->bit[next] < k) {
            k -= f->bit[next];
            idx = next;
        }
    }
    return idx + 1;
}

int cmp_ll(const void *a, const void *b) {
    ll x = *(const ll*)a, y = *(const ll*)b;
    return (x < y) ? -1 : (x > y);
}
int lower_bound_ll(ll *a, int n, ll x) 
{ 
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (a[mid] < x) lo = mid + 1; else hi = mid;
    }
    return lo;
}

/* ---------- основная функция ---------- */
int minimumSumSubarray(int* nums, int n, int l, int r) {
    ll *pref = (ll*)malloc((n + 1) * sizeof(ll));
    pref[0] = 0;
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + nums[i];

    ll *vals = (ll*)malloc((n + 1) * sizeof(ll));
    for (int i = 0; i <= n; ++i) vals[i] = pref[i];
    qsort(vals, n + 1, sizeof(ll), cmp_ll);
    // unique
    int m = 0;
    for (int i = 0; i <= n; ++i) {
        if (i == 0 || vals[i] != vals[i - 1]) vals[m++] = vals[i];
    }
    int *comp = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; ++i) {
        int pos = lower_bound_ll(vals, m, pref[i]); 
        comp[i] = pos + 1; 
    }

    Fenwick fw = fenw_create(m);
    ll best = LLONG_MAX;

    for (int right = 1; right <= n; ++right) {
        int addIdx = right - l;        
        int remIdx = right - r - 1;    

        if (addIdx >= 0) fenw_add(&fw, comp[addIdx], +1);
        if (remIdx >= 0) fenw_add(&fw, comp[remIdx], -1);

        int posLess = lower_bound_ll(vals, m, pref[right]); 
        int cntLess = fenw_sum(&fw, posLess);               
        if (cntLess > 0) {
            int idxPred = fenw_find_by_order(&fw, cntLess); 
            ll valPred = vals[idxPred - 1];
            ll diff = pref[right] - valPred; 
            if (diff > 0 && diff < best) best = diff;
        }
    }

    free(pref);
    free(vals);
    free(comp);
    free(fw.bit);

    return (best == LLONG_MAX) ? -1 : (int)best;
}

/* ---- пример ----
int main() {
    int a1[] = {3, -2, 1, 4};
    printf("%d\n", minimumSumSubarray(a1, 4, 2, 3)); // 1

    int a2[] = {-2, 2, -3, 1};
    printf("%d\n", minimumSumSubarray(a2, 4, 2, 3)); // -1

    int a3[] = {1, 2, 3, 4};
    printf("%d\n", minimumSumSubarray(a3, 4, 2, 4)); // 3

    int a4[] = {-3, 17};
    printf("%d\n", minimumSumSubarray(a4, 2, 1, 2)); // 14
}
*/
