
cmake_minimum_required(VERSION 3.14)
project(Boost_Test CXX)

link_directories(src)
file(GLOB SRC_FILES include/*.h src/*.cpp)

set(CMAKE_INSTALL_PREFIX install/)

set(BOOST_INCLUDEDIR "E:/Software/CPP_Libraries/boost/include/boost-1_69")
set(BOOST_LIBRARYDIR "E:/Software/CPP_Libraries/boost/lib")
set(BOOST_ROOT "E:/Software/CPP_Libraries/boost")

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
SET(BUILD_SHARED_LIBS OFF)
SET(CMAKE_EXE_LINKER_FLAGS "-static")

find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} include)
    add_executable(${PROJECT_NAME} ${SRC_FILES})
    target_link_libraries(${PROJECT_NAME} ${Boost_REGEX_LIBRARY} ${Boost_SYSTEM_LIBRARY}  -static)
endif()