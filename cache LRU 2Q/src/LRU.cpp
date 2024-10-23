#include <iostream>
#include "LRU.hpp"

void lookup_update_LRU (Hashtable & map, cacheList & lst, int elem, int & hits) {
    
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
