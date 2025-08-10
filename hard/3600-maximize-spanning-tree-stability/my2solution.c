#include <stdlib.h>
#include <limits.h>

typedef struct {
    int u, v;
    int s;
} Edge;

typedef struct {
    int *id;
    int n;
} UF;

static UF* uf_create(int n) {
    UF *uf = malloc(sizeof(UF));
    uf->n = n;
    uf->id = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) uf->id[i] = i;
    return uf;
}

static int uf_find(UF *uf, int x) {
    while (x != uf->id[x]) {
        uf->id[x] = uf->id[uf->id[x]];
        x = uf->id[x];
    }
    return x;
}

static int uf_union(UF *uf, int u, int v) {
    u = uf_find(uf, u);
    v = uf_find(uf, v);
    if (u == v) return 0;
    uf->id[u] = v;
    return 1;
}

static void uf_free(UF *uf) {
    free(uf->id);
    free(uf);
}

static int cmp_edges_desc(const void *a, const void *b) {
    const Edge *ea = (const Edge*)a;
    const Edge *eb = (const Edge*)b;
    if (ea->s < eb->s) return 1;
    if (ea->s > eb->s) return -1;
    return 0;
}

// Формат функции, как ты попросил
int maxStability(int n, int** edges, int edgesSize, int* edgesColSize, int k) {
    UF *uf = uf_create(n);
    int min_s = INT_MAX;
    int cou = n - 1;

    // Массив для необязательных рёбер
    Edge *remain = malloc(edgesSize * sizeof(Edge));
    int remain_count = 0;

    for (int i = 0; i < edgesSize; i++) {
        int n1 = edges[i][0];
        int n2 = edges[i][1];
        int s = edges[i][2];
        int must = edges[i][3];

        if (must) {
            if (!uf_union(uf, n1, n2)) {
                uf_free(uf);
                free(remain);
                return -1;
            }
            if (s < min_s) min_s = s;
            cou--;
        } else {
            remain[remain_count].u = n1;
            remain[remain_count].v = n2;
            remain[remain_count].s = s;
            remain_count++;
        }
    }

    if (cou == 0) {
        uf_free(uf);
        free(remain);
        return min_s;
    }

    qsort(remain, remain_count, sizeof(Edge), cmp_edges_desc);

    for (int i = 0; i < remain_count; i++) {
        if (uf_union(uf, remain[i].u, remain[i].v)) {
            int s = remain[i].s;
            if (cou <= k) {
                if (s * 2 < min_s) min_s = s * 2;
            } else {
                if (s < min_s) min_s = s;
            }
            cou--;
            if (cou == 0) {
                uf_free(uf);
                free(remain);
                return min_s;
            }
        }
    }

    uf_free(uf);
    free(remain);
    return -1;
}
