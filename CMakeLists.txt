# CMake
cmake_minimum_required(VERSION 3.16)

# Project Info
set(PROJECT_NAME openworld)
project(${PROJECT_NAME})

# Compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra  -Wpedantic -Wno-unused-parameter")

# Project source files
set(SOURCE_FILES
        main/main.cpp
        shader/Shader.cpp
        camera/Camera.cpp
        game/Game.cpp
        model/Model.cpp
        model/TerrainModel.cpp
        mesh/Mesh.cpp
        mesh/TerrainMesh.cpp
        texture/Texture.cpp
        window/WindowManager.cpp
        window/WindowException.cpp
        keyboard/Keyboard.cpp)

# Executables
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Include directories (ALL STATIC)
set(INCLUDE_DIRECTORIES libs/glfw-3.3/include libs/glew-2.1.0/include libs/glm)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRECTORIES})

# Link libraries
set(LINK_LIBRARIES ${CMAKE_SOURCE_DIR}/libs/glew-2.1.0/lib/libGLEW.a -lglfw -lGL -lX11 -lpthread -lXi -ldl)
target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARIES})



