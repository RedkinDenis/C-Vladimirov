#pragma once

#include <unordered_map>
#include <list>

typedef int TPage;

using namespace std;

typedef list<TPage> List;

struct cacheList {
    List lst;
    size_t listSize = 0;
};

typedef unordered_map<TPage, List::iterator> Hashtable;