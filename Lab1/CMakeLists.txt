cmake_minimum_required(VERSION 3.14)
project(FearChecker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()


add_executable(fear_checker_app
    src/main.cpp
    src/fear_checker.cpp
)


target_include_directories(fear_checker_app PRIVATE ${CMAKE_SOURCE_DIR}/include)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_fear_checker
    tests/test_fear_checker.cpp
    src/fear_checker.cpp
)


target_include_directories(test_fear_checker PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_fear_checker gtest_main)


add_test(NAME RunFearCheckerTests COMMAND test_fear_checker)