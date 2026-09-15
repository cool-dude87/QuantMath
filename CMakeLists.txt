# setting the standard library

cmake_minimum_required(VERSION 3.10)

project(BenMath)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# tell Cmake about vector cpp and enable the ability to access headers in module

add_library(BenMath
    src/Vector.cpp
)

target_include_directories(BenMath PUBLIC 
    include
)

# add test example 
add_executable(vector_test
    examples/vector_test.cpp    
)   

target_link_libraries(vector_test
    BenMath
)
