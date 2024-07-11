add_library(otsu src/otsu_threshold.cpp src/threshold.cpp src/otsu_threshold.h src/threshold.h include/otsu.h)
target_include_directories(otsu PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
install(TARGETS otsu)