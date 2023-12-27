cmake_minimum_required(VERSION 3.10.0)

project(engine)

SET(CMAKE_CXX_COMPILER g++)

set(GRAPHICS_SOURCES 
    engine/src/engine.cpp
    graphics/src/graphics-api.cpp
    graphics/src/graphics-engine-sdl.cpp
    main.cpp)

set(ENGINE_SOURCES 
    ${GRAPHICS_SOURCES})

set(ENGINE_LIBS
    stdc++ opengl32 glu32 sdl2)

set(ENGINE_INCLUDES
    engine/api
    engine/inc
    graphics/api
    graphics/inc)

add_executable(engine ${ENGINE_SOURCES})

target_link_libraries(engine ${ENGINE_LIBS})

target_include_directories(engine PUBLIC ${ENGINE_INCLUDES})