#include <iostream>
#include "../include/LRU-2Q.hpp"

struct cacheList {
    List lst;
    size_t listSize = 0;
};

static void new_page (Hashtable* map, cacheList* lst, int elem, int* hits);

int count_hits (const char* testName) {
    FILE* testFile = fopen(testName, "rb");

    int page = 0;
    int hits = 0;

    cacheList lst;
    Hashtable map;

    fscanf(testFile, "%d", &lst.listSize);
    
    while (fscanf(testFile, "%d", &page) != EOF) {
        new_page(&map, &lst, page, &hits);
    }
    return hits;
}

void new_page (Hashtable* map, cacheList* lst, int elem, int* hits) {
    
    if (map->count(elem) == 0)  {
        if (lst->lst.size() > lst->listSize) {
            lst->lst.pop_back();
        }
    }
    else {
        *hits += 1;

        lst->lst.erase(map->find(elem)->second);
        map->erase(elem);
    }

    lst->lst.push_front(elem);
    map->insert({elem, lst->lst.begin()});
}

void list_dump (List lst) {
    printf("LIST DUMP: ");
    List lst_cpy = lst;
    for (int i = 0; i < lst_cpy.size(); i++) {
        printf("%d ", *(lst_cpy.begin()++));
        lst_cpy.pop_front();
    }
    printf("\n");
}