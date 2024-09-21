# cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -S . -B build

cmake_minimum_required(VERSION 3.10)
project(lru2q)

set(CMAKE_CXX_STANDARD 17)

set(CMake_CXX_Compiler g++)

# enable_testing()

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

# set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
# include_directories(${TEST_DIR})

SET(SRCS1
    src/LRU.cpp
    src/LRU-2Q.cpp
)

SET(SRCS2
    src/ideal_cache.cpp
)

add_library(lru2Q STATIC ${SRCS1})
add_library(lruId STATIC ${SRCS2})

add_executable(lru2q.x main2Q.cpp)
target_link_libraries(lru2q.x lru2Q)

add_executable(lruId.x mainId.cpp)
target_link_libraries(lruId.x lruId)