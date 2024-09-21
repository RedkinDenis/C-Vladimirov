#ifndef LRU_H
#define LRU_H

#include <unordered_map>
#include <list>

using namespace std;

typedef list<int> List;
typedef unordered_map<int, List::iterator> Hashtable;

struct cacheList;

int count_hits_LRU (const char* testName);

void new_page_LRU (Hashtable & map, cacheList & lst, int elem, int & hits);

#endif // LRU_H