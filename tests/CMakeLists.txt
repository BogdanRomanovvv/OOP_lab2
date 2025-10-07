# tests/CMakeLists.txt
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(twelve_tests twelve_test.cpp)
target_link_libraries(twelve_tests PRIVATE gtest_main lab_02_lib)
target_include_directories(twelve_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
include(GoogleTest)
gtest_discover_tests(twelve_tests)

# На некоторых конфигурациях gtest_discover_tests может не зарегистрировать тесты для ctest;
# добавим простую явную привязку на всякий случай.
add_test(NAME twelve_tests COMMAND twelve_tests)
