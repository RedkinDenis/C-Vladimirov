#include <iostream>
#include "LRU.hpp"

struct cacheList {
    List lst;
    size_t listSize = 0;
};

int count_hits_LRU (const char* testName) {

    FILE* testFile = fopen(testName, "rb");

    int page = 0;
    int hits = 0;

    cacheList lst;
    Hashtable map;

    fscanf(testFile, "%d", &lst.listSize);
    
    while (fscanf(testFile, "%d", &page) == 1) {
        new_page_LRU(map, lst, page, hits);
    }
    
    int result = 0;
    fscanf(testFile, "answer - %d", &result);
    
    if (result == hits) {
        printf("SUCCESS hits - %d\n", hits);
    }
    else {
        printf("FAILED");
    }

    return hits;
}

void new_page_LRU (Hashtable & map, cacheList & lst, int elem, int & hits) {
    
    if (map.count(elem) == 0)  {
        if (lst.lst.size() == lst.listSize) {

            map.erase(lst.lst.back());
            lst.lst.pop_back();
        }
    }
    else {
        
        hits += 1;

        lst.lst.erase(map.find(elem)->second);
        map.erase(elem);
    }

    lst.lst.push_front(elem);
    map.insert({elem, lst.lst.begin()});
}
