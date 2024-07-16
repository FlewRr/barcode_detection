cmake_minimum_required(VERSION 3.5)

project(main)

find_package(OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS} )

add_subdirectory(image_processing)
add_subdirectory(detection)

add_executable(main main.cpp )
target_link_libraries(main ${OpenCV_LIBS} img_fltr otsu gradient hough detection)
