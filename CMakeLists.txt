cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_CXX_FLAGS "-std=c++0x -std=c++11 ${CMAKE_CXX_FLAGS}")

add_executable(timeit timeit.cpp)
target_link_libraries(timeit ${CORELIBS})

