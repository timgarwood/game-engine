cmake_minimum_required(VERSION 3.10.0)

project(engine)

SET(BULLET_PHYSICS_DEMO 1)
SET(CMAKE_BUILD_TYPE Debug)

SET(CMAKE_CXX_COMPILER g++)

if(SINGLE_POINT_DEMO)
add_compile_definitions(SINGLE_POINT_DEMO)
set(DEMO_SOURCES
    main.cpp
    demo/single-point-demo.cpp
)
elseif(TRIANGLE_DEMO)
add_compile_definitions(TRIANGLE_DEMO)
set(DEMO_SOURCES
    main.cpp
    demo/triangle-demo.cpp
)
elseif(SHADER_UNIFORM_DEMO)
add_compile_definitions(SHADER_UNIFORM_DEMO)
set(DEMO_SOURCES
    main.cpp
    demo/shader-uniform-demo.cpp
)
elseif(SHADER_TRANSLATION_DEMO)
add_compile_definitions(SHADER_TRANSLATION_DEMO)
set(DEMO_SOURCES
    main.cpp
    demo/shader-translation-demo.cpp
)
elseif(SHADER_ROTATION_DEMO)
add_compile_definitions(SHADER_ROTATION_DEMO)
set(DEMO_SOURCES
    main.cpp
    demo/shader-rotation-demo.cpp
)
elseif(SHADER_INTERPOLATION_DEMO)
add_compile_definitions(SHADER_INTERPOLATION_DEMO)
set(DEMO_SOURCES
    main.cpp
    demo/shader-interpolation-demo.cpp
)
elseif(INDEX_BUFFER_DEMO)
add_compile_definitions(INDEX_BUFFER_DEMO)
set(DEMO_SOURCES
    main.cpp
    demo/index-buffer-demo.cpp
)
elseif(PERSPECTIVE_PROJECTION_DEMO)
add_compile_definitions(PERSPECTIVE_PROJECTION_DEMO)
set(DEMO_SOURCES
    main.cpp
    demo/perspective-projection-demo.cpp
)
elseif(BULLET_HELLO_WORLD)
set(DEMO_SOURCES
    demo/bullet-hello-world.cpp
)
elseif(BULLET_PHYSICS_DEMO)
set(DEMO_SOURCES
    demo/bullet-physics-demo-main.cpp
    demo/bullet-physics-demo.cpp
)

endif()

set(ENGINE_SOURCES 
    engine/src/engine.cpp
)

set(MATH_SOURCES math/matrix.cpp
    math/vector.cpp
    math/quaternion.cpp)

SET(FILE_SOURCES
    file/file-utils.cpp
)

set(GRAPHICS_SOURCES 
    graphics/src/graphics-engine-sdl.cpp)

set(INPUT_SOURCES
    input/sdl-event-dispatcher.cpp)

set(CAMERA_SOURCES
    camera/camera.cpp
    camera/fps-camera-controller.cpp)

set(GAME_SOURCES
    game/game-object.cpp
    game/game-world.cpp
    game/game-object-renderer.cpp
    game/cube.cpp
    game/quad3d.cpp
    )

set(SHADER_SOURCES 
    shaders/shader-parser.cpp
    shaders/shader-factory.cpp
    shaders/shader-program.cpp) 

set(PHYSICS_SOURCES
    physics/bullet-physics-engine.cpp
    )

set(DEBUG_SOURCES
    debug/debug-scene-data.cpp
    debug/debug-scene-parser.cpp
    debug/debug-scene-factory.cpp
    )

set(ENGINE_LIBS
    stdc++ opengl32 glu32 sdl2 glew32 jsoncpp BulletDynamics BulletCollision LinearMath)

set(ENGINE_INCLUDES
    file
    window
    math
    demo
    camera
    engine/api
    engine/inc
    graphics/inc
    input
    shaders
    game
    physics
    debug
    )

# TODO fixme
# not sure why I need to do this???
set(BULLET_INCLUDES
    D:/msys64/ucrt64/include/bullet
    D:/msys64/ucrt64/include/bullet/LinearMath
    D:/msys64/ucrt64/include/bullet/src/LinearMath)

add_executable(engine ${ENGINE_SOURCES} ${DEBUG_SOURCES} ${PHYSICS_SOURCES} ${MATH_SOURCES} ${GRAPHICS_SOURCES} ${INPUT_SOURCES} ${CAMERA_SOURCES} ${DEMO_SOURCES} ${FILE_SOURCES} ${SHADER_SOURCES} ${GAME_SOURCES})

target_link_libraries(engine ${ENGINE_LIBS})

target_include_directories(engine PUBLIC ${ENGINE_INCLUDES} ${BULLET_INCLUDES})