cmake_minimum_required(VERSION 3.10.0)

project(raycaster)

SET(CMAKE_BUILD_TYPE Debug)
SET(PATH_TO_ENGINE ..)

SET(CMAKE_CXX_COMPILER g++)

set(DEMO_SOURCES
    raycaster.cpp
    main.cpp
)

set(ENGINE_SOURCES 
    ${PATH_TO_ENGINE}/engine/src/engine.cpp
)

set(MATH_SOURCES
    ${PATH_TO_ENGINE}/math/vector.cpp
    ${PATH_TO_ENGINE}/math/quaternion.cpp
    )

SET(FILE_SOURCES
    ${PATH_TO_ENGINE}/file/file-utils.cpp
)

set(GRAPHICS_SOURCES 
    ${PATH_TO_ENGINE}/graphics/src/graphics-engine-sdl.cpp)

set(INPUT_SOURCES
    ${PATH_TO_ENGINE}/input/sdl-event-dispatcher.cpp)

set(ENGINE_LIBS
    stdc++ opengl32 glu32 sdl2 glew32 jsoncpp)

set(ENGINE_INCLUDES
    ${PATH_TO_ENGINE}/file
    ${PATH_TO_ENGINE}/window
    ${PATH_TO_ENGINE}/math
    ${PATH_TO_ENGINE}/demo
    ${PATH_TO_ENGINE}/camera
    ${PATH_TO_ENGINE}/engine/api
    ${PATH_TO_ENGINE}/engine/inc
    ${PATH_TO_ENGINE}/graphics/inc
    ${PATH_TO_ENGINE}/input
    ${PATH_TO_ENGINE}/debug
    )

add_executable(raycaster ${ENGINE_SOURCES} ${MATH_SOURCES} ${GRAPHICS_SOURCES} ${INPUT_SOURCES} ${DEMO_SOURCES} ${FILE_SOURCES})

target_link_libraries(raycaster ${ENGINE_LIBS})

target_include_directories(raycaster PUBLIC ${ENGINE_INCLUDES})