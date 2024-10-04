#include <iostream>
#include <stdlib.h>
#include <containers.hpp>
#include <ideal_cache.hpp>
#include <LRU-2Q.hpp>

static TPage* get_data (int* numberOfPages);

static void new_page (TPage* pages, int currentPageNumber, int numberOfPages, Hashtable & map, cacheList & lst, int & hits);

static TPage find_latest_page (TPage* pages, int currentPageNumber, int numberOfPages, Hashtable & map, cacheList & list);

// bool seek_in_future (TPage* pages, int currentPageNumber, int numberOfPages, size_t listSize);

using namespace std;

TPage* get_data (int* numberOfPages) {

    cin >> *numberOfPages;

    TPage* pages = (TPage*)calloc(*numberOfPages, sizeof(TPage));
    for (int i = 0; i < *numberOfPages; i++) {

        cin >> pages[i];
    }

    return pages;
}

int count_hits_Ideal_cache () {

    // printf("here\n");
    int hits = 0;
    cacheList lst;
    Hashtable hashTable;

    cin >> lst.listSize;
    int numberOfPages = 0;
    TPage* pages = get_data(&numberOfPages);


    for (int i = 0; i < numberOfPages; i++) {

        // scanf("%d", &pages[i]);
        new_page(pages, i, numberOfPages, hashTable, lst, hits);
    }

    // printf("hits - %d\n", hits);
    return hits;
}

void new_page (TPage* pages, int currentPageNumber, int numberOfPages, Hashtable & map, cacheList & lst, int & hits) {

    // printf("\nelem - %d\n", pages[currentPageNumber]);
    // if (lst.lst.size() == lst.listSize && 
    //     seek_in_future(pages, currentPageNumber, numberOfPages, lst.listSize) == false &&
    //     map.count(pages[currentPageNumber]) == 0) {
    //     return;
    // }

    if (map.count(pages[currentPageNumber]) == 0) {

        if (lst.lst.size() < lst.listSize) {

            // printf("\nPUSH - %d\n", pages[currentPageNumber]);

            lst.lst.push_front(pages[currentPageNumber]);
            map.insert({pages[currentPageNumber], lst.lst.begin()});
        }
        else {

            TPage latestPage = find_latest_page(pages, currentPageNumber, numberOfPages, map, lst);

            if (latestPage == pages[currentPageNumber]) {
                
                // printf("\nIGNORE - %d\n", pages[currentPageNumber]);
                return;
            }

            // printf("\nDELETE - %d and\n", latestPage);
            lst.lst.erase(map.find(latestPage)->second);
            map.erase(latestPage);

            // printf("PUSH - %d\n", pages[currentPageNumber]);
            lst.lst.push_front(pages[currentPageNumber]);
            map.insert({pages[currentPageNumber], lst.lst.begin()});        
        }
    }
    else {

        // printf ("\nHIT\n");
        hits += 1;
    }
}

TPage find_latest_page (TPage* pages, int currentPageNumber, int numberOfPages, Hashtable & map, cacheList & list) {

    List lstCp = list.lst;
    lstCp.push_back(pages[currentPageNumber]);

    for (auto p : lstCp) {

        bool check = false;
        for (int i = currentPageNumber + 1; i < numberOfPages; i++) {

            if (pages[i] == p) {

                check = true;
            }
        }    

        if (check == false) {

            return p;
        }
    }

    TPage latestPage = pages[currentPageNumber];
    for (int i = currentPageNumber + 1; i < numberOfPages; i++) {

        if (map.count(pages[i]) != 0) {

            latestPage = pages[i];
        }

        else if (pages[i] == pages[currentPageNumber]) {

            latestPage = pages[currentPageNumber];
        }
    }
    return latestPage;
}

// bool seek_in_future (TPage* pages, int currentPageNumber, int numberOfPages, size_t listSize) {

//     // cout << pages[currentPageNumber];
//     for (int i = currentPageNumber + 1; /*(i < currentPageNumber + 1 + listSize) && */(i < numberOfPages); i++) {

//         if (pages[i] == pages[currentPageNumber]) {

//             // cout << " true" << endl;
//             return true;
//         }
//     }
//     // cout << " false" << endl;
//     return false;
// }