#include <iostream>
#include "LRU-2Q.hpp"
#include "LRU.hpp"
#include "containers.hpp"

struct Q2Lists {
    cacheList lstAm;
    cacheList lstA1In;
    cacheList lstA1Out;

    inline void set_lists_size (size_t cacheSize) {

        if (cacheSize > 3) {
            
            lstAm.listSize = cacheSize / 2;        
            lstA1In.listSize = (cacheSize - lstAm.listSize) / 2;
            lstA1Out.listSize = cacheSize - lstAm.listSize - lstA1In.listSize;
        }
        else {

            lstAm.listSize = cacheSize;
        }
        printf ("\nAmSize - %d INSize - %d OutSize - %d\n", lstAm.listSize, lstA1In.listSize, lstA1Out.listSize);
    }
};

struct Q2HashTables {
    Hashtable mapAm;
    Hashtable mapIn;
    Hashtable mapOut;
};

static void new_page_2Q (Q2HashTables & map, Q2Lists & lst, TPage elem, int & hits);

int count_hits_2Q () {

    // FILE* testFile = fopen(testName, "rb");

    TPage page = 0;
    int hits = 0;

    Q2Lists lists;
    Q2HashTables hashTables;    

    int cacheSize = 0;
    scanf("%d", &cacheSize);

    int pageCount = 0;
    scanf("%d", &pageCount);

    lists.set_lists_size(cacheSize);
    

    if (cacheSize > 3) {

        for (int i = 0; i < pageCount; i++) {

            scanf("%d", &page);
            new_page_2Q(hashTables, lists, page, hits);
        }
    }

    else {

        for (int i = 0; i < pageCount; i++) {

            scanf("%d", &page);
            new_page_LRU(hashTables.mapAm, lists.lstAm, page, hits);
        }
    }

    return hits;
}

void new_page_2Q (Q2HashTables & map, Q2Lists & lst, TPage elem, int & hits) {

    // printf("elem - %d ", elem);
    if (map.mapAm.count(elem) == 0) { 

        if (map.mapIn.count(elem) == 0) {

            if (map.mapOut.count(elem) == 0) {
            
                // printf("PUSH TO IN ");
                if (lst.lstA1In.listSize == lst.lstA1In.lst.size()) {

                    if (lst.lstA1Out.lst.size() == lst.lstA1Out.listSize) {

                        map.mapOut.erase(lst.lstA1Out.lst.back());
                        lst.lstA1Out.lst.pop_back();
                    }

                    // printf("MOVE FROM IN TO OUT ");
                    lst.lstA1Out.lst.push_front(lst.lstA1In.lst.back());
                    map.mapOut.insert({lst.lstA1In.lst.back(), lst.lstA1Out.lst.begin()});

                    map.mapIn.erase(lst.lstA1In.lst.back());
                    lst.lstA1In.lst.pop_back();
                }
                lst.lstA1In.lst.push_front(elem);
                map.mapIn.insert({elem, lst.lstA1In.lst.begin()});
            }

            else {

                // printf("MOVE FROM OUT TO AM ");

                lst.lstA1Out.lst.erase(map.mapOut.find(elem)->second);
                map.mapOut.erase(elem);

                if (lst.lstAm.lst.size() == lst.lstAm.listSize) {

                    map.mapAm.erase(lst.lstAm.lst.back());
                    lst.lstAm.lst.pop_back();
                }

                lst.lstAm.lst.push_front(elem);
                map.mapAm.insert({elem, lst.lstAm.lst.begin()});
            }
        }

        else {

            hits += 1;

            // printf("MOVE FROM IN TO IN ");

            lst.lstA1In.lst.erase(map.mapIn.find(elem)->second);
            map.mapIn.erase(elem);

            lst.lstA1In.lst.push_front(elem);
            map.mapIn.insert({elem, lst.lstA1In.lst.begin()});
        }
    }

    else {

        hits += 1;

        // printf("MOVE FROM AM TO AM ");

        lst.lstAm.lst.erase(map.mapAm.find(elem)->second);
        map.mapAm.erase(elem);

        lst.lstAm.lst.push_front(elem);
        map.mapAm.insert({elem, lst.lstAm.lst.begin()});
    }
    printf("\n");
}