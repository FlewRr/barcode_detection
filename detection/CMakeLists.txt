add_library(detection src/detector.cpp src/markup.cpp src/metrics.cpp include/detection.h)
target_include_directories(detection PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
install(TARGETS detection)
target_link_libraries(detection pugixml)
