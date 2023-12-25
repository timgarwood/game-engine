cmake_minimum_required(VERSION 3.10.0)

project(engine)

SET(CMAKE_CXX_COMPILER g++)

set(ENGINE_SOURCES 
    test.cpp)

set(ENGINE_LIBS
    stdc++ opengl32 glu32 sdl2)

add_executable(engine ${ENGINE_SOURCES})

target_link_libraries(engine ${ENGINE_LIBS})