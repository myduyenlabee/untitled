cmake_minimum_required(VERSION 3.23)
project(untitled)


set(CMAKE_MODULE_PATH $ {PROJECT_SOURCE_DIR}/CMAKE)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(untitled main.cpp duyen.h)
add_executable(untitled1 baitap.cpp)
target_link_libraries(untitled ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows)
