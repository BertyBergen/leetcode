
#define EMPTY_KEY INT_MIN 

typedef struct
{
    int key;
    int index;
} 
Data;

typedef struct 
{
    Data *data;
    int capacity;   
}
HashMap;

static inline unsigned int hash_int(int x)
{
    unsigned int h = (unsigned int) x;
    h ^= h >> 16;
    h *= 0x7feb352d;
    h ^= h >> 15;
    h *= 0x846ca68b;
    h ^= h >> 16;
    return h;
}

HashMap *hm_create(int cap)
{
    HashMap *hm = malloc(sizeof *hm);
    if (!hm) return NULL;
    hm->capacity = cap;
    hm->data = malloc((sizeof * hm->data )* cap);
    if (!hm->data)
    {
        free(hm);
        return NULL;
    }

    for (int i = 0; i < cap; ++i)
    {
        hm->data[i].key = EMPTY_KEY;
        hm->data[i].index = -1;
    }
    return hm;
}

int hm_put(HashMap *hm, int key, int index)
{
    unsigned int mask = hm->capacity - 1;
    unsigned int h = hash_int(key) & mask;
    for (;;)
    {
        if (hm->data[h].key == EMPTY_KEY)
        {
            hm->data[h].key = key;
            hm->data[h].index = index;
            return 1;
        }
        if (hm->data[h].key == key)
        {
            hm->data[h].index = index;
            return 1;
        }
        
        h = (h + 1) & mask;
    }
}

int hm_get(HashMap *hm, int key)
{
    unsigned int mask = hm->capacity - 1;
    unsigned int h = hash_int(key) & mask;
    for (;;)
    {
        if (hm->data[h].key == EMPTY_KEY) return -1;
        if (hm->data[h].key == key) return hm->data[h].index;
        h = (h + 1) & mask;
    }

}

void hm_free(HashMap *hm)
{
    if (!hm) return;
    free(hm->data);
    free(hm);
}

bool containsNearbyDuplicate(int* nums, int numsSize, int k) 
{
    int cap = 1;
    while (cap < numsSize * 2) cap <<= 1;
    HashMap *hm = hm_create(cap);
    if (!hm) return NULL;

    int min_index = numsSize+1;

    for (int i = 0; i < numsSize; ++i)
    {
        int check = hm_get(hm, nums[i]);
        if (check != -1 && i - check <= k)
        {
            hm_free(hm);
            return true;
        }
        hm_put(hm, nums[i], i);
    } 
    return false;
    // if abs(i - j) <= k return true
    // else return false
}