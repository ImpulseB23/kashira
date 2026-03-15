cmake_minimum_required(VERSION 3.20)
project(kashira-tests)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.13.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests
    test_curves.cpp
    ../habaki/src-tauri/blades/timeshift/wakefulness.cpp
    ../habaki/src-tauri/blades/timeshift/availability.cpp
    ../habaki/src-tauri/common/timeutil.c
)

target_include_directories(tests PRIVATE ../habaki/src-tauri/blades/timeshift ../habaki/src-tauri/common)
target_link_libraries(tests Catch2::Catch2WithMain)
