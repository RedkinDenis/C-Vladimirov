#ifndef LRU_2Q_H
#define LRU_2Q_H

#include <iostream>

#include "containers.hpp"
#include "LRU.hpp"

// typedef int TPage;

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
        // printf ("\nAmSize - %d INSize - %d OutSize - %d\n", lstAm.listSize, lstA1In.listSize, lstA1Out.listSize);
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

            if (cacheSize > 3) {

                for (int i = 0; i < pageCount; i++) {

                    std::cin >> page;
                    lookup_update(page, hits);
                }
            }

            else {

                for (int i = 0; i < pageCount; i++) {

                    std::cin >> page;
                    new_page_LRU(hashTables.mapAm, lists.lstAm, page, hits);
                }
            }

            return hits;
        }

    private:
    
        void lookup_update (TPage elem, int & hits) {

            // printf("elem - %d ", elem);
            if (hashTables.mapAm.count(elem) == 0) { 

                if (hashTables.mapIn.count(elem) == 0) {

                    if (hashTables.mapOut.count(elem) == 0) {
                    
                        // printf("PUSH TO IN ");
                        if (lists.lstA1In.listSize == lists.lstA1In.lst.size()) {

                            if (lists.lstA1Out.lst.size() == lists.lstA1Out.listSize) {

                                hashTables.mapOut.erase(lists.lstA1Out.lst.back());
                                lists.lstA1Out.lst.pop_back();
                            }

                            // printf("MOVE FROM IN TO OUT ");
                            lists.lstA1Out.lst.push_front(lists.lstA1In.lst.back());
                            hashTables.mapOut.insert({lists.lstA1In.lst.back(), lists.lstA1Out.lst.begin()});

                            hashTables.mapIn.erase(lists.lstA1In.lst.back());
                            lists.lstA1In.lst.pop_back();
                        }
                        lists.lstA1In.lst.push_front(elem);
                        hashTables.mapIn.insert({elem, lists.lstA1In.lst.begin()});
                    }

                    else {

                        // printf("MOVE FROM OUT TO AM ");

                        lists.lstA1Out.lst.erase(hashTables.mapOut.find(elem)->second);
                        hashTables.mapOut.erase(elem);

                        if (lists.lstAm.lst.size() == lists.lstAm.listSize) {

                            hashTables.mapAm.erase(lists.lstAm.lst.back());
                            lists.lstAm.lst.pop_back();
                        }

                        lists.lstAm.lst.push_front(elem);
                        hashTables.mapAm.insert({elem, lists.lstAm.lst.begin()});
                    }
                }

                else {

                    hits += 1;

                    // printf("MOVE FROM IN TO IN ");

                    lists.lstA1In.lst.erase(hashTables.mapIn.find(elem)->second);
                    hashTables.mapIn.erase(elem);

                    lists.lstA1In.lst.push_front(elem);
                    hashTables.mapIn.insert({elem, lists.lstA1In.lst.begin()});
                }
            }

            else {

                hits += 1;

                // printf("MOVE FROM AM TO AM ");

                lists.lstAm.lst.erase(hashTables.mapAm.find(elem)->second);
                hashTables.mapAm.erase(elem);

                lists.lstAm.lst.push_front(elem);
                hashTables.mapAm.insert({elem, lists.lstAm.lst.begin()});
            }
        }
};

// int count_hits_2Q ();

#endif // LRU_2Q_H