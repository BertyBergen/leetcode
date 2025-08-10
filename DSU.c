#include <stdio.h>
#include <stdlib.h>

// Структура для ребра
typedef struct {
    int u;
    int v;
    int strength;
    int must;
    int need_upgrade; // 0 - без апгрейда, 1 - с апгрейдом
} Edge;

// DSU с ранговой оптимизацией и сжатием пути
typedef struct {
    int *parent;
    int *rank;
    int n;
} DSU;

DSU* dsu_create(int n) {
    DSU *dsu = malloc(sizeof(DSU));
    dsu->n = n;
    dsu->parent = malloc(sizeof(int)*n);
    dsu->rank = malloc(sizeof(int)*n);
    for (int i=0; i<n; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
    }
    return dsu;
}

void dsu_free(DSU *dsu) {
    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
}

int dsu_find(DSU *dsu, int x) {
    if (dsu->parent[x] != x)
        dsu->parent[x] = dsu_find(dsu, dsu->parent[x]);
    return dsu->parent[x];
}

int dsu_union(DSU *dsu, int x, int y) {
    int xr = dsu_find(dsu, x);
    int yr = dsu_find(dsu, y);
    if (xr == yr) return 0; // Уже в одной компоненте

    // Прикрепляем дерево с меньшим рангом к большему
    if (dsu->rank[xr] < dsu->rank[yr]) {
        dsu->parent[xr] = yr;
    } else if (dsu->rank[yr] < dsu->rank[xr]) {
        dsu->parent[yr] = xr;
    } else {
        dsu->parent[yr] = xr;
        dsu->rank[xr]++;
    }
    return 1;
}

// Компаратор для qsort — сортируем по need_upgrade (сначала 0, потом 1)
int cmp_by_upgrade(const void *a, const void *b) {
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    return ea->need_upgrade - eb->need_upgrade;
  

}

// can_build проверяет, можно ли построить остов с данной стабильностью
int can_build(int n, Edge *edges, int edges_count, int k, int stability) {
    DSU *dsu = dsu_create(n);
    int count = 0;          // сколько ребер добавлено
    int used_upgrades = 0;  // сколько апгрейдов использовано

    // Массив для необязательных рёбер
    Edge *optional_edges = malloc(sizeof(Edge)*edges_count);
    int optional_count = 0;

    // Сначала обрабатываем обязательные ребра (must == 1)
    for (int i=0; i<edges_count; i++) {
        if (edges[i].must == 1) {
            // Если прочность обязательного ребра меньше stability — сразу False
            if (edges[i].strength < stability) {
                dsu_free(dsu);
                free(optional_edges);
                return 0;
            }
            if (dsu_union(dsu, edges[i].u, edges[i].v)) {
                count++;
            }
        } else {
            // Необязательные рёбра отбираем по условию
            if (edges[i].strength >= stability) {
                edges[i].need_upgrade = 0;
                optional_edges[optional_count++] = edges[i];
            } else if (edges[i].strength * 2 >= stability) {
                edges[i].need_upgrade = 1;
                optional_edges[optional_count++] = edges[i];
            }
            // Иначе ребро слишком слабое — игнорируем
        }
    }

    // Сортируем необязательные ребра так, чтобы сначала шли без апгрейда
    qsort(optional_edges, optional_count, sizeof(Edge), cmp_by_upgrade);

    // Добавляем необязательные ребра в остов, пока не достигнем n-1 ребра
    for (int i=0; i<optional_count; i++) {
        if (optional_edges[i].need_upgrade == 1 && used_upgrades >= k)
            continue; // апгрейдов больше нет

        if (dsu_union(dsu, optional_edges[i].u, optional_edges[i].v)) {
            count++;
            if (optional_edges[i].need_upgrade == 1)
                used_upgrades++;
            if (count == n-1)
                break;
        }
    }

    int result = (count == n-1);

    dsu_free(dsu);
    free(optional_edges);
    return result;
}

// maxStability — бинарный поиск по стабильности
int maxStability(int n, Edge *edges, int k) {
    // Находим максимально возможную верхнюю границу по стабильности
    int edges_count = sizeof(edges) / sizeof(edges[0]);
    int max_strength = 0;
    for (int i=0; i<edges_count; i++) {
        int val = edges[i].strength * 2; // возможный апгрейд
        if (val > max_strength)
            max_strength = val;
    }

    int low = 0, high = max_strength, result = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (can_build(n, edges, edges_count, k, mid)) {
            result = mid;
            low = mid + 1; // пытаемся поднять стабильность выше
        } else {
            high = mid - 1;
        }
    }
    return result;
}

// --- Пример использования ---
int main() {
    // Пример: 4 вершины, 5 рёбер, можно улучшить k=1 ребро
    int n = 4;
    int k = 1;
    int edges_count = 5;

    Edge edges[] = {
        {0, 1, 4, 1, 0},
        {1, 2, 5, 0, 0},
        {2, 3, 2, 0, 0},
        {3, 0, 2, 0, 0},
        {1, 3, 3, 0, 0},
    };

    int answer = maxStability(n, edges, k);
    printf("Максимальная стабильность: %d\n", answer);

    return 0;
}
