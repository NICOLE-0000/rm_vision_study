cmake_minimum_required(VERSION 3.10)

project(day3_hsv)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

# 程序1：色彩空间对比
add_executable(color_space color_space.cpp)
target_link_libraries(color_space ${OpenCV_LIBS})

# 程序2：HSV 调参神器（核心）
add_executable(hsv_trackbar hsv_trackbar.cpp)
target_link_libraries(hsv_trackbar ${OpenCV_LIBS})

# 程序3：手写 inRange 对比
add_executable(manual_inrange manual_inrange.cpp)
target_link_libraries(manual_inrange ${OpenCV_LIBS})

# 程序4：视频实时处理
add_executable(video_hsv video_hsv.cpp)
target_link_libraries(video_hsv ${OpenCV_LIBS})
