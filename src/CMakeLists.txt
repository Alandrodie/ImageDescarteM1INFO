set(CMAKE_CXX_FLAGS "-std=c++11")

# CMake version
cmake_minimum_required(VERSION 3.1)




# Project name
project(CodeBarreDetection)
# Used libraries
find_package(OpenCV REQUIRED)


# Source files
set(SOURCES PreProcess.h PreProcess.cpp  CodeBarreDetection.h CodeBarreDetection.cpp )
# Output files
add_executable(codeDetection main.cpp ${SOURCES})
# Link libraries to output files
target_link_libraries(codeDetection ${OpenCV_LIBS})




