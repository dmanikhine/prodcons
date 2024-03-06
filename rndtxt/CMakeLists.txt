cmake_minimum_required(VERSION 3.20)
project(rndtxt)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Boost 1.82.0 REQUIRED COMPONENTS program_options)
message(${Boost_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
add_executable(rndtxt main.cpp cmdoptions.cpp testascii.cpp)
target_compile_options(rndtxt PRIVATE -O3) #tail recursion

TARGET_LINK_LIBRARIES(rndtxt ${Boost_LIBRARIES})




