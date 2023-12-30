cmake_minimum_required(VERSION 3.10.0)

project(engine)

SET(TRIANGLE_DEMO 1)

SET(CMAKE_CXX_COMPILER g++)

if(SINGLE_POINT_DEMO)
add_compile_definitions(SINGLE_POINT_DEMO)
set(DEMO_SOURCES
    demo/single-point-demo.cpp
)
elseif(TRIANGLE_DEMO)
add_compile_definitions(TRIANGLE_DEMO)
set(DEMO_SOURCES
    demo/triangle-demo.cpp
)
endif()

set(ENGINE_SOURCES 
    engine/src/engine.cpp
)

set(GRAPHICS_SOURCES 
    graphics/src/graphics-engine-sdl.cpp
    main.cpp)

set(ENGINE_LIBS
    stdc++ opengl32 glu32 sdl2 glew32)

set(ENGINE_INCLUDES
    math
    demo
    engine/api
    engine/inc
    graphics/inc)

add_executable(engine main.cpp ${ENGINE_SOURCES} ${GRAPHICS_SOURCES} ${DEMO_SOURCES})

target_link_libraries(engine ${ENGINE_LIBS})

target_include_directories(engine PUBLIC ${ENGINE_INCLUDES})