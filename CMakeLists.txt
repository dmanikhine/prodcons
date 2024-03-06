cmake_minimum_required(VERSION 3.20)
project(prodcons)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Boost 1.82.0 REQUIRED COMPONENTS thread program_options)
message(${Boost_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

add_executable(prodcons main.cpp readfile.cpp transformline.cpp smalltools.cpp cmdoptions.cpp)

TARGET_LINK_LIBRARIES(prodcons ${Boost_LIBRARIES})