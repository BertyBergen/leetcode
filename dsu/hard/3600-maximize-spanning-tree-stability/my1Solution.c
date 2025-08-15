#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *parent;
    int *rank;
    int size;
} DSU;

typedef struct
{
    int u;
    int v;
    int strength;
    int must;
    int need_upgrade;
} Edge;

DSU *dsu_create(int size)
{
    DSU *dsu = malloc(sizeof *dsu);
    if (!dsu) return NULL;
    dsu->size = size;

    dsu->parent = malloc(sizeof(int) * size);
    if (!dsu->parent) { free(dsu); return NULL; }
    dsu->rank = calloc(size, sizeof(int));
    if (!dsu->rank) { free(dsu->parent); free(dsu); return NULL; }
    for (int i = 0; i < size; i++)
    {
        dsu->parent[i] = i;
    }
    return dsu;
}

void dsu_free(DSU *dsu)
{
    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
}

int dsu_find(DSU *dsu, int x)
{   
    if (dsu->parent[x] != x)
    {
        dsu->parent[x] = dsu_find(dsu, dsu->parent[x]);
    }
    return dsu->parent[x];
}

int dsu_union(DSU *dsu, int x, int y)
{
    int rootX = dsu_find(dsu, x);
    int rootY = dsu_find(dsu, y);

    if (rootX == rootY) return 0;
    
    if (dsu->rank[rootX] < dsu->rank[rootY])
    {
        dsu->parent[rootX] = rootY;
    }    
    else if (dsu->rank[rootX] > dsu->rank[rootY])
    {
        dsu->parent[rootY] = rootX;
    }
    else
    {
        dsu->parent[rootY] = rootX;
        dsu->rank[rootX]++;
    }
    return 1;
}

int cmp_by_upgrade(const void *a, const void *b)
{
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;

    if (ea->need_upgrade != eb->need_upgrade)
        return ea->need_upgrade - eb->need_upgrade; 

    return eb->strength - ea->strength; 
}

int can_build(int n, Edge *edges,int edges_count, int k, int stability)
{
    DSU *dsu = dsu_create(n);
    int count = 0;
    int used_upgrades = 0;

    Edge *opt_edges = malloc(sizeof *opt_edges * edges_count);
    int opt_count = 0;

    for (int i = 0;  i < edges_count; i++)
    {
        if (edges[i].must == 1)
        {
            if (edges[i].strength < stability)
            {
                dsu_free(dsu);
                free(opt_edges);
                return 0;
            }
            if (dsu_union(dsu, edges[i].u, edges[i].v))
            {
                count++;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (edges[i].strength >=stability)
            {
                edges[i].need_upgrade = 0;
                opt_edges[opt_count++] = edges[i];
            }
            else if (edges[i].strength * 2 >= stability)
            {
                edges[i].need_upgrade = 1;
                opt_edges[opt_count++] = edges[i];
            }
        }
    }
    qsort(opt_edges, opt_count, sizeof(Edge), cmp_by_upgrade);

    for (int i = 0; i < opt_count; i++)
    {
        if (opt_edges[i].need_upgrade == 1 && used_upgrades >= k) continue;

        if (dsu_union(dsu, opt_edges[i].u, opt_edges[i].v))
        {
            count++;
            if (opt_edges[i].need_upgrade == 1) used_upgrades++;
            if (count == n-1) break;
        }
    } 
    int result = (count == n-1);

    dsu_free(dsu);
    free(opt_edges);
    return result;
}

int maxStability_helper(int n, Edge *edges, int edgesSize, int k)
{
    int max_strength = 0;
    for (int i = 0; i < edgesSize; i++)
    {
        int val = edges[i].strength * 2;
        if (val > max_strength) max_strength = val;
    }

    int low = 0, high = max_strength, result = -1;
    while (low <= high)
    {
        int mid = (low + high) /2;
        if (can_build(n, edges, edgesSize, k, mid))
        {
            result = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return result;
}
int maxStability(int n, int** edges, int edgesSize, int* edgesColSize, int k) 
{
    // Создаем массив структур Edge
    Edge *edge_arr = malloc(sizeof(Edge) * edgesSize);
    for (int i = 0; i < edgesSize; i++) 
    {
        edge_arr[i].u = edges[i][0];
        edge_arr[i].v = edges[i][1];
        edge_arr[i].strength = edges[i][2];
        edge_arr[i].must = edges[i][3];
        edge_arr[i].need_upgrade = 0; 
    }

    int result = maxStability_helper(n, edge_arr, edgesSize, k);

    free(edge_arr);
    return result;
}
