cmake_minimum_required(VERSION 3.10.0)

project(engine)

SET(PERSPECTIVE_PROJECTION_DEMO 1)
SET(CMAKE_BUILD_TYPE Debug)

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
elseif(SHADER_UNIFORM_DEMO)
add_compile_definitions(SHADER_UNIFORM_DEMO)
set(DEMO_SOURCES
    demo/shader-uniform-demo.cpp
)
elseif(SHADER_TRANSLATION_DEMO)
add_compile_definitions(SHADER_TRANSLATION_DEMO)
set(DEMO_SOURCES
    demo/shader-translation-demo.cpp
)
elseif(SHADER_ROTATION_DEMO)
add_compile_definitions(SHADER_ROTATION_DEMO)
set(DEMO_SOURCES
    demo/shader-rotation-demo.cpp
)
elseif(SHADER_INTERPOLATION_DEMO)
add_compile_definitions(SHADER_INTERPOLATION_DEMO)
set(DEMO_SOURCES
    demo/shader-interpolation-demo.cpp
)
elseif(INDEX_BUFFER_DEMO)
add_compile_definitions(INDEX_BUFFER_DEMO)
set(DEMO_SOURCES
    demo/index-buffer-demo.cpp
)
elseif(PERSPECTIVE_PROJECTION_DEMO)
add_compile_definitions(PERSPECTIVE_PROJECTION_DEMO)
set(DEMO_SOURCES
    demo/perspective-projection-demo.cpp
)
endif()

set(ENGINE_SOURCES 
    engine/src/engine.cpp
)

SET(FILE_SOURCES
    file/file-utils.cpp
)

set(GRAPHICS_SOURCES 
    graphics/src/graphics-engine-sdl.cpp)

set(ENGINE_LIBS
    stdc++ opengl32 glu32 sdl2 glew32)

set(ENGINE_INCLUDES
    file
    math
    demo
    engine/api
    engine/inc
    graphics/inc)

add_executable(engine main.cpp ${ENGINE_SOURCES} ${GRAPHICS_SOURCES} ${DEMO_SOURCES} ${FILE_SOURCES})

target_link_libraries(engine ${ENGINE_LIBS})

target_include_directories(engine PUBLIC ${ENGINE_INCLUDES})