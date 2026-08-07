cmake_minimum_required(VERSION 3.10)

project(day_2_mat_basics)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

#程序1：图像读写
add_executable(readWriteImage readWriteImage.cpp)
target_link_libraries(readWriteImage ${OpenCV_LIBS})

#程序2：绿色图像
add_executable(greenImage greenImage.cpp)
target_link_libraries(greenImage ${OpenCV_LIBS})

#程序3：装甲板检测器测试
add_executable(armor_detector_test armor_detector_test.cpp)
target_link_libraries(armor_detector_test ${OpenCV_LIBS})
