add_library(hough src/hough.cpp src/aux.cpp src/hough.h src/aux.h include/hough_transform.h)
target_include_directories(hough PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
install(TARGETS hough)