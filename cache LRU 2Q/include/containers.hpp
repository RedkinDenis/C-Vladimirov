#ifndef CONTAINERS_HPP
#define CONTAINERS_HPP

#include <unordered_map>
#include <list>

// #include "LRU-2Q.hpp"
typedef int TPage;

using namespace std;

typedef list<TPage> List;

struct cacheList {
    List lst;
    size_t listSize = 0;
};

typedef unordered_map<TPage, List::iterator> Hashtable;

#endif // CONTAINERS_HPP