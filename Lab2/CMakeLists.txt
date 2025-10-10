cmake_minimum_required(VERSION 3.16)
project(Lab2_Seven LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# ---------------- GOOGLE TEST SECTION ----------------
# Встроенная загрузка GoogleTest через FetchContent (современный способ)
include(FetchContent)
# ...
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    # Используйте тег с префиксом 'v'
    GIT_TAG        v1.15.0 
    # В качестве альтернативы, можно попробовать v1.15.2, так как это более свежий патч
    # GIT_TAG        v1.15.2 
)
# ...
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Собираем тесты
file(GLOB TEST_FILES ${CMAKE_SOURCE_DIR}/tests/*.cpp)
add_executable(UnitTests ${TEST_FILES} ${SRC_FILES})
target_include_directories(UnitTests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(UnitTests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(UnitTests)
