cmake_minimum_required(VERSION 2.8)

Project(Test1)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "-O1") 

include_directories(${OpenCV_INCLUDE_DIRS}) 
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src POCA_OPENCV_SRC)

add_executable(demo main.cpp ${POCA_OPENCV_SRC})
target_link_libraries(demo ${OpenCV_LIBS})