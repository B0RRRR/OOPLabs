cmake_minimum_required(VERSION 3.16)
project(Lab2_Seven LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_library(lab2 ${SRC_FILES})
target_include_directories(lab2
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


file(GLOB TEST_FILES ${CMAKE_SOURCE_DIR}/tests/*.cpp)
add_executable(UnitTests ${TEST_FILES})


target_link_libraries(UnitTests PRIVATE lab2 GTest::gtest_main)
target_include_directories(UnitTests PRIVATE ${CMAKE_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(UnitTests)
