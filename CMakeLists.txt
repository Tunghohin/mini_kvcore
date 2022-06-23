cmake_minimum_required(VERSION 3.22)
project(mini_kvcore)

set(CMAKE_CXX_STANDARD 14)

add_executable(mini_kvcore skip_list.h main.cpp)
