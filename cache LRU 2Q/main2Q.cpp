#include "LRU-2Q.hpp"
#include <iostream>

int main() {
    
    Lru2qCache cache;
    std::cout << cache.count_hits_2Q() << std::endl;
}