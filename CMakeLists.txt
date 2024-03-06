cmake_minimum_required(VERSION 3.20)
project(mtfind)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Boost 1.82.0 REQUIRED COMPONENTS thread program_options)
message(${Boost_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

add_executable(mtfind main.cpp readfile.cpp transformline.cpp smalltools.cpp cmdoptions.cpp concurrency.cpp)
target_compile_options(mtfind PRIVATE -O3) #tail recursion

TARGET_LINK_LIBRARIES(mtfind ${Boost_LIBRARIES})