# cmake -DCMAKE_BUILD_TYPE=Release -S . -B build

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
    src/geometry_elems.cpp
)


add_library(triangles STATIC ${SRCS1})

add_executable(triangles.x main.cpp)
target_link_libraries(triangles.x triangles)