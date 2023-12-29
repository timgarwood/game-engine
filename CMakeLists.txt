cmake_minimum_required(VERSION 3.10.0)

project(engine)

SET(CMAKE_CXX_COMPILER g++)

set(DEMO_SOURCES
    demo/single-point-demo.cpp
)

set(ENGINE_SOURCES 
    engine/src/engine.cpp
)

set(GRAPHICS_SOURCES 
    graphics/src/graphics-api.cpp
    graphics/src/graphics-engine-sdl.cpp
    main.cpp)

set(ENGINE_LIBS
    stdc++ opengl32 glu32 sdl2 glew32)

set(ENGINE_INCLUDES
    demo
    engine/api
    engine/inc
    graphics/api
    graphics/inc)

add_executable(engine main.cpp ${ENGINE_SOURCES} ${GRAPHICS_SOURCES} ${DEMO_SOURCES})

target_link_libraries(engine ${ENGINE_LIBS})

target_include_directories(engine PUBLIC ${ENGINE_INCLUDES})