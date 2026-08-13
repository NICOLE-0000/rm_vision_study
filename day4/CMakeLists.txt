cmake_minimum_required(VERSION 3.10)

project(day4_preprocess)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

add_executable(filter_compare filter_compare.cpp)
target_link_libraries(filter_compare ${OpenCV_LIBS})

add_executable(morphology_test morphology_test.cpp)
target_link_libraries(morphology_test ${OpenCV_LIBS})

add_executable(canny_trackbar canny_trackbar.cpp)
target_link_libraries(canny_trackbar ${OpenCV_LIBS})

add_executable(preprocess_pipeline preprocess_pipeline.cpp)
target_link_libraries(preprocess_pipeline ${OpenCV_LIBS})