#ifndef IDEAL_CACHE_HPP
#define IDEAL_CACHE_HPP

#include "LRU-2Q.hpp"
// #include "LRU.hpp"

#include <vector>
#include <algorithm>
#include <iterator>

#include <unordered_map>

class idealCache {

    public:

    std::vector<TPage> cache;
    std::unordered_map<TPage, std::vector<TPage>::iterator> hashtable;

    size_t sz;

    idealCache (size_t setSz) : sz(setSz) {}

    int check_hits_ideal_cache(std::vector<TPage> &pages) {

        int pagesCount = pages.size();
        int hits = 0;
        for(int currentPageNumber = 0; currentPageNumber < pagesCount; currentPageNumber++) { // std::find заменить хэш таблицей

            lookup_update1(pages, currentPageNumber, hits);
        }
        return hits;
    }

    private:

    void lookup_update2 (std::vector<TPage> &pages, int &currentPageNumber, int &hits) {

        if (hashtable.count(pages[currentPageNumber]) == 0) {

            if (cache.size() < sz) {

                cache.push_back(pages[currentPageNumber]);
                hashtable.insert({pages[currentPageNumber], pages.end() - 1});
                // printf("1 ");
            }

            else {

                auto inpIt = pages.begin();
                std::advance(inpIt, currentPageNumber + 1);

                auto max = hashtable.find(pages[currentPageNumber])->second, del = cache.begin();
                std::vector<TPage>::iterator pos;

                if (max != pages.end()) {

                    for (auto cacheIt = std::next(cache.begin()); cacheIt != cache.end(); ++cacheIt) {

                        pos = hashtable.find(pages[currentPageNumber])->second;

                        if (max < pos) {
                            max = pos;
                            del = cacheIt;
                        }

                        if (max == pages.end()) {

                            break;
                        }
                    }
                    // printf("2 ");

                }

                if (hashtable.find(pages[currentPageNumber])->second < max) {

                    hashtable.erase(*del);
                    cache.erase(del);
                    
                    cache.push_back(pages[currentPageNumber]);
                    hashtable.insert({pages[currentPageNumber], pages.end() - 1});

                    // printf("4 ");

                }
            }
            return;
        }

        // auto hitsCp = hits;
        // printf("5 ");

        hits++;

        // if (hits == hitsCp) printf("\nDOLBOEB\n");
    }

    void lookup_update1 (std::vector<TPage> &pages, int &currentPageNumber, int &hits) {

        if (hashtable.count(pages[currentPageNumber]) == 0) {

            if (cache.size() < sz) {

                cache.push_back(pages[currentPageNumber]);
                hashtable.insert({pages[currentPageNumber], pages.end() - 1});
                // printf("1 ");
            }

            else {

                auto inpIt = pages.begin();
                std::advance(inpIt, currentPageNumber + 1);

                auto max = std::find(inpIt, pages.end(), cache[0]), del = cache.begin();
                std::vector<TPage>::iterator pos;

                if (max != pages.end()) {

                    for (auto cacheIt = std::next(cache.begin()); cacheIt != cache.end(); ++cacheIt) {

                        pos = std::find(inpIt, pages.end(), *cacheIt);

                        if (max < pos) {
                            max = pos;
                            del = cacheIt;
                        }

                        if (max == pages.end()) {

                            break;
                        }
                    }
                    // printf("3 ");
                }

                if (std::find(inpIt, pages.end(), pages[currentPageNumber]) < max) {

                    hashtable.erase(*del);
                    cache.erase(del);
                    
                    cache.push_back(pages[currentPageNumber]);
                    hashtable.insert({pages[currentPageNumber], pages.end() - 1});
                    
                    // printf("4 ");
                }
            }
            return;
        }

        // auto hitsCp = hits;
        // printf("5 ");

        hits++;

        // if (hits == hitsCp) printf("\nDOLBOEB\n");
    }

};

#endif // IDEAL_CACHE_HPP