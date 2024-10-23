#pragma once

#include <unordered_map>
#include <list>

#include "containers.hpp"

void lookup_update_LRU (Hashtable & map, cacheList & lst, int elem, int & hits);