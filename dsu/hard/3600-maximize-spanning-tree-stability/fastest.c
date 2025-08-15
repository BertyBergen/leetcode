typedef struct {
    int u, v, w;
} Edge;

int components;

int findParent(int parent[], int u) {
    if (parent[u] == -1) return u;
    else return parent[u] = findParent(parent, parent[u]);
}

void unite(int parent[], int size[], int u, int v) {
    u = findParent(parent, u);
    v = findParent(parent, v);
    if (u == v) return;
    components--;
    if (size[u] > size[v]) {
        size[u] += size[v];
        parent[v] = u;
    } else {
        size[v] += size[u];
        parent[u] = v;
    }
}

void merge(int l, int r, int mid, Edge edges[]) {
    int i, j, k;
    int n1 = mid - l + 1;
    int n2 = r - mid;
    Edge L[n1], R[n2];
    for (i = 0; i < n1; i++) {
        L[i] = edges[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = edges[mid + 1 + j];
    }
    i = 0;
    j = 0;
    k = l; 
    while (i < n1 && j < n2) {
        if (L[i].w >= R[j].w) {
            edges[k] = L[i];
            i++;
        } else {
            edges[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        edges[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        edges[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int l, int r, Edge edges[]) {
    if (l < r) {
        int mid = (l + r) / 2;
        mergeSort(l, mid, edges);
        mergeSort(mid + 1, r, edges);
        merge(l, r, mid, edges);
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

int maxStability(int n, int** edges, int edgesSize, int* edgesColSize, int k) {
    components = n;    
    int parent[n];
    int size[n];
    for (int i = 0; i < n; i++) parent[i] = -1, size[i] = 1;
    Edge optionalEdges[edgesSize];
    int optionalEdgesCount = 0;
    int ans = INT_MAX;
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2], must = edges[i][3];
        if (must) {
            if (findParent(parent, u) == findParent(parent, v)) return -1;
            unite(parent, size, u, v);
            ans = min(ans, w);
        } else {
            Edge e; e.u = u, e.v = v, e.w = w;
            optionalEdges[optionalEdgesCount++] = e;
        }
    }
    mergeSort(0, optionalEdgesCount - 1, optionalEdges);
    int taken[edgesSize];
    int track_idx = 0;
    for (int i = 0; i < optionalEdgesCount; i++) {
        int u = optionalEdges[i].u, v = optionalEdges[i].v;
        if (findParent(parent, u) == findParent(parent, v)) continue;
        unite(parent, size, u, v);
        taken[track_idx++] = optionalEdges[i].w;
    }
    if (components > 1) return -1; 
    for (int i = track_idx - 1; k && i >= 0; i--, k--) {
        taken[i] *= 2;
    }
    for (int i = track_idx - 1; i >= 0; i--) {
        ans = min(ans, taken[i]);
    }
    return ans;
}