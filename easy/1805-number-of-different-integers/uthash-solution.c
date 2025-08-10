typedef struct {
    char *id;         // string key
    UT_hash_handle hh; // makes this struct hashable uthash
} hashmap_entry;

// Add or update an entry
bool add_entry(hashmap_entry **hashmap, const char *key) {
    hashmap_entry *entry = NULL;

    HASH_FIND_STR(*hashmap, key, entry);  // search
    if (entry == NULL) {
        entry = (hashmap_entry*) malloc(sizeof(hashmap_entry));
        entry->id = strdup(key);        // must strdup so it's safely owned
        HASH_ADD_KEYPTR(hh, *hashmap, entry->id, strlen(entry->id), entry);  // add to hash
        return true;
    } else {
        return false;
    }
}

// Lookup
hashmap_entry* find_entry(hashmap_entry *hashmap, const char *key) {
    hashmap_entry *entry = NULL;
    HASH_FIND_STR(hashmap, key, entry);
    return entry;
}

// Delete
void delete_entry(hashmap_entry *hashmap, const char *key) {
    hashmap_entry *entry;
    HASH_FIND_STR(hashmap, key, entry);
    if (entry) {
        HASH_DEL(hashmap, entry);
        free(entry->id);
        free(entry);
    }
}

// Cleanup
void free_all(hashmap_entry *hashmap) {
    hashmap_entry *current, *tmp;
    HASH_ITER(hh, hashmap, current, tmp) {
        HASH_DEL(hashmap, current);
        free(current->id);
        free(current);
    }
}

char* removeLeadingZeros(char* str) {
    int i = 0;
    // Find the index of the first non-zero character or the null terminator
    while (str[i] == '0' && str[i+1] != '\0') {
        i++;
    }
    return &str[i]; // Return a pointer to the first non-zero character
}

int numDifferentIntegers(char* word) {

    // we will replace every non digit with a space
    // then we will use strtok to get each string
    // each token will be added to a dictionary and we increment ans, if we attempt to add a token that already
    // exists in the dictionary we do NOT increment ans

    // we need to remove leading zeroes for "001" so we just end up with "1"
    // converting to an integer using strtol or atoi can lead to an integer overflow so dont do it

    if (word == NULL) {
        return 0;
    }

    int wordLen = strlen(word);
    int ans = 0;

    // replace every digit with a space
    for (int i = 0; i < wordLen; i++) {
        if (word[i] > '9') {
            word[i] = ' ';
        }
    }

    char *token = strtok(word, " ");
    hashmap_entry *newMap = NULL;
    
    while (token != NULL) {
        // printf("%s KEK\n", token);
        char *newToken= removeLeadingZeros(token);
        bool ret = add_entry(&newMap, newToken);
        if (ret) {
            ans++;
        }
        token = strtok(NULL, " ");
    }

    // free the hash map
    free_all(newMap);
    return ans;
}