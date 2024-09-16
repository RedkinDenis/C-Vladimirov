#ifndef LRU_H
#define LRU_H

#include <unordered_map>
#include <list>

using namespace std;

typedef list<int> List;
typedef unordered_map<int, List::iterator> Hashtable;

int count_hits_LRU (const char* testName);

#endif // LRU_H