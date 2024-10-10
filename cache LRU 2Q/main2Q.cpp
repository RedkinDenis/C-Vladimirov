#include "LRU-2Q.hpp"
#include <iostream>

using namespace std;

int main() {
    
    Lru2qCache cache;
    cout << cache.count_hits_2Q() << endl;
}