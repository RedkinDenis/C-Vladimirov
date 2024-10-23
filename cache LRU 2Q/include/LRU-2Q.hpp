#pragma once

#include <iostream>

#include "containers.hpp"
#include "LRU.hpp"

#define LRU2Q_MIN_CACHE_SIZE 3

struct Q2Lists {

    cacheList lstAm;
    cacheList lstA1In;
    cacheList lstA1Out;

    inline void set_lists_size (size_t cacheSize) {

        if (cacheSize > LRU2Q_MIN_CACHE_SIZE) {
            
            lstAm.listSize = cacheSize / 2;        
            lstA1In.listSize = (cacheSize - lstAm.listSize) / 2;
            lstA1Out.listSize = cacheSize - lstAm.listSize - lstA1In.listSize;
        }
        else {
            
            lstAm.listSize = cacheSize;
        }
    }
};

struct Q2HashTables {

    Hashtable mapAm;
    Hashtable mapIn;
    Hashtable mapOut;
};

class Lru2qCache {

    Q2Lists lists;
    Q2HashTables hashTables; 

    public:

        int count_hits_2Q () {

            TPage page = 0;
            int hits = 0;

            int cacheSize = 0;
            std::cin >> cacheSize;

            int pageCount = 0;
            std::cin >> pageCount;

            lists.set_lists_size(cacheSize);

            if (cacheSize > LRU2Q_MIN_CACHE_SIZE) {

                for (int i = 0; i < pageCount; i++) {

                    std::cin >> page;
                    lookup_update(page, hits);
                }
            }

            else {

                for (int i = 0; i < pageCount; i++) {

                    std::cin >> page;
                    lookup_update_LRU(hashTables.mapAm, lists.lstAm, page, hits);
                }
            }

            return hits;
        }

    private:
    
        void lookup_update (TPage elem, int & hits) {

            if (hashTables.mapAm.count(elem) == 0) { 

                if (hashTables.mapIn.count(elem) == 0) {

                    if (hashTables.mapOut.count(elem) == 0) {
                    
                        if (lists.lstA1In.listSize == lists.lstA1In.lst.size()) {

                            if (lists.lstA1Out.lst.size() == lists.lstA1Out.listSize) {

                                delete_from_cache(lists.lstA1Out, hashTables.mapOut);
                            }

                            add_to_cache(lists.lstA1Out, hashTables.mapOut, lists.lstA1In.lst.back());

                            delete_from_cache(lists.lstA1In, hashTables.mapIn);
                        }
                        
                        add_to_cache(lists.lstA1In, hashTables.mapIn, elem);

                        return;
                    }

                    delete_from_cache(lists.lstA1Out, hashTables.mapOut, elem);

                    if (lists.lstAm.lst.size() == lists.lstAm.listSize) {

                        delete_from_cache(lists.lstAm, hashTables.mapAm);
                    }

                    add_to_cache(lists.lstAm, hashTables.mapAm, elem);

                    return;
                }

                hits += 1;

                delete_from_cache(lists.lstA1In, hashTables.mapIn, elem);

                add_to_cache(lists.lstA1In, hashTables.mapIn, elem);

                return;
            }

            hits += 1;

            delete_from_cache(lists.lstAm, hashTables.mapAm, elem);

            add_to_cache(lists.lstAm, hashTables.mapAm, elem);
        }

        void add_to_cache (cacheList &list, Hashtable &map, TPage elem) {

            list.lst.push_front(elem);
            map.insert({elem, list.lst.begin()});
        }

        // delete by search in map
        void delete_from_cache (cacheList &list, Hashtable &map, TPage elem) {

            list.lst.erase(map.find(elem)->second);
            map.erase(elem);
        }

        // delete from list's tail
        void delete_from_cache (cacheList &list, Hashtable &map) {

            map.erase(list.lst.back());
            list.lst.pop_back();
        }
};