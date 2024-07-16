add_library(detection src/detector.cpp src/detector.h include/detection.h)
target_include_directories(detection PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
install(TARGETS detection)