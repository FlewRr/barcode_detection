add_library(image_processing 
            src/blur.cpp
            src/filter.cpp
            src/hough.cpp 
            src/otsu_threshold.cpp 
            src/sobel.cpp 
            src/threshold.cpp 
            include/blur.h
            include/filter.h 
            include/hough.h 
            include/otsu_threshold.h
            include/sobel.h
            include/threshold.h 
            include/image_processing.h)
target_include_directories(image_processing PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
install(TARGETS image_processing)