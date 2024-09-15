# cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -S . -B build

cmake_minimum_required(VERSION 3.10)
project(huy)

set(CMAKE_CXX_STANDARD 17)

set(CMake_CXX_Compiler g++)

# enable_testing()

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

# set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
# include_directories(${TEST_DIR})

SET(SRCS
    # src/main.cpp
    src/LRU-2Q.cpp
)

add_library(lru2Q STATIC ${SRCS})
# target_include_directories(lru2Q PUBLIC "include")
# target_link_libraries(lru2Q PUBLIC "include")

add_executable(lru.x main.cpp)
target_link_libraries(lru.x lru2Q)