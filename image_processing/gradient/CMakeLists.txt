add_library(gradient sobel/sobel.cpp sobel/sobel.h include/gradient.h)
target_include_directories(gradient PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
install(TARGETS gradient)