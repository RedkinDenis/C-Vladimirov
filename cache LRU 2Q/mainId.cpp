#include "ideal_cache.hpp"
#include "LRU-2Q.hpp"
#include <vector>
#include <iostream>

int main() {
    int sz;
    std::cin >> sz;
    if (std::cin.bad()) {
        std::cerr << "Incorrect input size cache\n";
        return 1;
    }

    std::vector<TPage> data;
    idealCache cache(sz);

    // std::cout << "cache max_size - " << cache.cache.max_size() << std::endl;

    int num;
    std::cin >> num;
    if (std::cin.bad()) {
        std::cerr << "Incorrect input size \n";
        return 1;
    }

    int val;
    for(int i = 0; i < num; i++) {
        std::cin >> val;
        if (std::cin.bad()) {
        std::cerr << "Incorrect input value\n";
        return 1;
    }
        data.push_back(val);
    }

    int hits;
    hits = cache.check_hits_ideal_cache(data);
    std::cout << "Number of hits: " << hits << '\n';
}