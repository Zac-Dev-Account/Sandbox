cmake_minimum_required(VERSION 3.14)
project(FractalImages CXX)
include_directories(include)
link_directories(src)
file(GLOB SRC_FILES include/*.h src/*.cpp)

set(CMAKE_INSTALL_PREFIX install/)

add_executable(${PROJECT_NAME} ${SRC_FILES})