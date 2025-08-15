#include "dsu.h"

DSU* dsu_create(int size) {
    DSU *dsu = malloc(sizeof(DSU));
    dsu->size = size;
    dsu->parent = malloc(size * sizeof(int));
    dsu->rank = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
    }
    return dsu;
}

void dsu_free(DSU *dsu) {
    if (dsu) {
        free(dsu->parent);
        free(dsu->rank);
        free(dsu);
    }
}

int dsu_find(DSU *dsu, int x) {
    if (dsu->parent[x] != x) {
        dsu->parent[x] = dsu_find(dsu, dsu->parent[x]); // сжатие путей
    }
    return dsu->parent[x];
}

int dsu_union(DSU *dsu, int x, int y) {
    int rootX = dsu_find(dsu, x);
    int rootY = dsu_find(dsu, y);
    if (rootX == rootY) return 0;

    // объединяем по рангу
    if (dsu->rank[rootX] < dsu->rank[rootY]) {
        dsu->parent[rootX] = rootY;
    } else if (dsu->rank[rootX] > dsu->rank[rootY]) {
        dsu->parent[rootY] = rootX;
    } else {
        dsu->parent[rootY] = rootX;
        dsu->rank[rootX]++;
    }
    return 1;
}
