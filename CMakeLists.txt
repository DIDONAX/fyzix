cmake_minimum_required(VERSION 3.16)
project(fyzix LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB SOURCES engine/src/*.cpp)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SOURCE_DIR _deps/SFML
)

FetchContent_MakeAvailable(SFML)

#DEMO
add_executable(test exe/test.cpp ${SOURCES})

include_directories(engine/include)

target_link_libraries(test PRIVATE SFML::Graphics)
