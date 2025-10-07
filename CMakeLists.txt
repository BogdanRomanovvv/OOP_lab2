cmake_minimum_required(VERSION 3.16)
project(lab_02)

# Указываем директорию с заголовочными файлами
include_directories(${PROJECT_SOURCE_DIR}/include)

# Включаем тестирование (делаем это на верхнем уровне, чтобы ctest корректно видел тесты)
enable_testing()

# Создаём основную библиотеку из исходников
add_library(lab_02_lib
    src/myarray.cpp
    src/twelve.cpp
)
target_include_directories(lab_02_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Добавляем директорию с тестами
add_subdirectory(tests)
