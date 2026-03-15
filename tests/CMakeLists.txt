cmake_minimum_required(VERSION 3.20)
project(hilt-tests)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(catch2)

add_executable(tests
    test_curves.cpp
    ../src-tauri/blades/timeshift/curves.cpp
)

target_include_directories(tests PRIVATE ../src-tauri/blades/timeshift)
target_link_libraries(tests Catch2::Catch2WithMain)
