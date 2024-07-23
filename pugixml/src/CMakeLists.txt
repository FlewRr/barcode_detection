cmake_minimum_required(VERSION 3.5)
add_library(pugixml pugixml.cpp pugixml.hpp)
target_include_directories(pugixml PUBLIC  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>   
    $<INSTALL_INTERFACE:> ) 
    
install(TARGETS pugixml)