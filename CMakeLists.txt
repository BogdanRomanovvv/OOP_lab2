cmake_minimum_required(VERSION 3.16)
project(lab_02)

include_directories(${PROJECT_SOURCE_DIR}/include)

enable_testing()

add_library(lab_02_lib
    src/myarray.cpp
    src/twelve.cpp
)
target_include_directories(lab_02_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(lab_02_app src/main.cpp)
target_link_libraries(lab_02_app PRIVATE lab_02_lib)

add_subdirectory(tests)
