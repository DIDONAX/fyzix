cmake_minimum_required(VERSION 3.16)
project(ddx_engine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main
)

FetchContent_MakeAvailable(SDL3)

file(GLOB_RECURSE SOURCE "src/*.cpp" "include/*.h")

add_executable(ddx_engine ${SOURCE})
target_include_directories(ddx_engine PRIVATE include)
target_link_libraries(ddx_engine PRIVATE SDL3::SDL3)
