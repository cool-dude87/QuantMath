# setting the standard library

cmake_minimum_required(VERSION 3.10)

project(QuantMath)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# tell Cmake about vector cpp and enable the ability to access headers in module

add_library(QuantMath
    src/Vector.cpp
    src/Matrix.cpp
)

target_include_directories(QuantMath PUBLIC 
    include
)

# add test example 
add_executable(vector_test
    examples/vector_test.cpp   
    examples/functions.cpp 
    examples/functions.h 
    examples/main.cpp  
)   

target_link_libraries(vector_test
    QuantMath
)
