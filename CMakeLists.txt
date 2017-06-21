cmake_minimum_required(VERSION 3.7)
project(PoP_PDF_project)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp lib/tinyxml2/tinyxml2.cpp main.h)
add_executable(PoP_PDF_project ${SOURCE_FILES})
