cmake_minimum_required(VERSION 3.10)

project(day1_hello_rm)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED Ture)


find_package(OpenCV REQUIRED)

add_executable(hello_rm hello_rm.cpp)

target_link_libraries(hello_rm ${OpenCV_LIBS})