#ifndef IDEAL_CACHE_HPP
#define IDEAL_CACHE_HPP

#include "LRU-2Q.hpp"

#include <vector>
#include<algorithm>
#include<iterator>

class idealCache {

    public:

    std::vector<TPage> cache;
    size_t sz;

    idealCache (size_t setSz) : sz(setSz) {}

    int check_hits_ideal_cache(std::vector<TPage> &pages) {

        int pagesCount = pages.size();
        int hits = 0;
        for(int currentPageNumber = 0; currentPageNumber < pagesCount; currentPageNumber++) { // std::find заменить хэш таблицей

            lookup_update(pages, currentPageNumber, hits);
        }
        return hits;
    }

    private:

    void lookup_update (std::vector<TPage> &pages, int &currentPageNumber, int &hits) {

        if (std::find(cache.begin(), cache.end(), pages[currentPageNumber]) == cache.end()) {

            if (cache.size() < sz) {

                cache.push_back(pages[currentPageNumber]);
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
                }

                if (std::find(inpIt, pages.end(), pages[currentPageNumber]) < max) {
                    cache.erase(del);
                    cache.push_back(pages[currentPageNumber]);
                }
            }
            return;
        }

        // auto hitsCp = hits;

        hits++;

        // if (hits == hitsCp) printf("\nDOLBOEB\n");
    }
};

#endif // IDEAL_CACHE_HPP