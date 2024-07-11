add_library(img_fltr src/blur.cpp src/filter.cpp src/blur.h src/filter.h include/img_fltr.h)
target_include_directories(img_fltr PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
install(TARGETS img_fltr)