#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node
{
    char *key;
    struct Node *next;
};

typedef struct
{
    struct Node **buckets;
    int capacity;
    int size;
} HashMap;

unsigned int hash_str(const char *str) {
    unsigned int h = 2166136261u;
    while (*str) {
        h ^= (unsigned char)(*str++);
        h *= 16777619;
    }
    return h;
}

HashMap *hm_create(int cap)
{
    HashMap *hm = malloc(sizeof *hm);
    if (!hm) return NULL;
    hm->capacity = cap;
    hm->size = 0;
    hm->buckets = calloc(cap, sizeof(struct Node *));
    if (!hm->buckets) 
    {
        free(hm);
        return NULL;
    }
    return hm;
}

int hm_exists(HashMap *hm, const char *key)
{
    unsigned int h = hash_str(key) % hm->capacity;
    struct Node *cur = hm->buckets[h];
    while (cur)
    {
        if (strcmp(cur->key, key) == 0) return 1;
        cur = cur->next;
    }
    return 0;
}

void hm_insert(HashMap *hm, const char *key)
{
    if (hm_exists(hm, key)) return;
    unsigned int h = hash_str(key) % hm->capacity;
    struct Node *node = malloc(sizeof *node);
    node->key = strdup(key);
    node->next = hm->buckets[h];
    hm->buckets[h] = node;
    hm->size++;
}

void hm_free(HashMap *hm)
{
    for (int i = 0; i < hm->capacity; i++)
    {
   
        struct Node *cur = hm->buckets[i];
        while(cur)
        {
            struct Node *tmp = cur;
            cur = cur->next;
            free(tmp->key);
            free(tmp);
        }
        
    }
    free(hm->buckets);
    free(hm);
}

void append_char(char **buf, int *buf_len, int *buf_cap, char c) {
    if (*buf_len + 1 >= *buf_cap) {
        *buf_cap = (*buf_cap == 0) ? 128 : (*buf_cap * 2);
        *buf = realloc(*buf, *buf_cap);
    }
    (*buf)[(*buf_len)++] = c;
}

void flush_number(char **buf, int *buf_len, HashMap *hm) {
    if (*buf_len == 0) return;
    (*buf)[*buf_len] = '\0';
    int start = 0;
    while ((*buf)[start] == '0' && (*buf)[start + 1] != '\0') {
        start++;
    }
    hm_insert(hm, *buf + start);
    *buf_len = 0;
}

int numDifferentIntegers(char *word)
{
    HashMap *hm = hm_create(256);
    char *buf = NULL;
    int buf_len = 0;
    int buf_cap = 0;

    for (char *p = word;;p++)
    {
        if (*p && isdigit((unsigned char)*p))
        {
            append_char(&buf, &buf_len,&buf_cap, *p);
        }
        else
        {
            flush_number(&buf, &buf_len, hm);
            if (!*p) break;
        }
    }
    int res = hm->size;
    hm_free(hm);
    free(buf);
    return res;
}