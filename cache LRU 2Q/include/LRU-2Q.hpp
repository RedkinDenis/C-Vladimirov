#ifndef LRU_2Q_H
#define LRU_2Q_H

#include <unordered_map>
#include <list>

typedef int TPage;

using namespace std;

// template<typename Page>
typedef list<TPage> List;
// typedef list<TPage> ListOut;

// template<typename Page>
typedef unordered_map<TPage, List::iterator> Hashtable;
// typedef unordered_map<TPage, ListOut::iterator> HashtableOut; // return pointer

int count_hits_2Q (const char* testName);

#endif // LRU_2Q_H