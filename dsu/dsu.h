#ifndef DSU_H
#define DSU_H

#include <stdlib.h>

// Структура DSU
typedef struct {
    int *parent;
    int *rank;
    int size;
} DSU;

// Создать DSU на size элементов
DSU* dsu_create(int size);

// Освободить память DSU
void dsu_free(DSU *dsu);

// Найти корень множества, к которому принадлежит x
int dsu_find(DSU *dsu, int x);

// Объединить множества, содержащие x и y
// Возвращает 1, если произошло объединение, 0 — если уже в одном множестве
int dsu_union(DSU *dsu, int x, int y);

#endif // DSU_H
