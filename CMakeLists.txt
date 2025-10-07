cmake_minimum_required(VERSION 3.16)
project(lab_02)

include_directories(${PROJECT_SOURCE_DIR}/include)

enable_testing()

add_library(lab_02_lib
    src/myarray.cpp
    src/twelve.cpp
)
target_include_directories(lab_02_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(tests)
