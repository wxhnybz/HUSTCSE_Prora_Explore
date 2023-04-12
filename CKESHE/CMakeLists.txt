cmake_minimum_required(VERSION 3.24)
project(CKESHE)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(CMAKE_CXX_STANDARD 17)

add_executable(GSM main.cpp )
add_executable(a test.cpp)