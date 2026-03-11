# Specify CMake version(s)
cmake_minimum_required(VERSION 3.15...4.3)

# Declare project
project(
    raytracer
    VERSION 1.0
    LANGUAGES C CXX
)

# Compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default build type (adds -O3)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Declare the executable
add_executable(${PROJECT_NAME})

# Add source files
target_sources(${PROJECT_NAME} PRIVATE
    # ./src/
    src/main.cpp

    # ./src/screen_source/
    src/screen_source/myTexture.cpp
    src/screen_source/screenFuncs.cpp
    src/screen_source/screenQuad.cpp
    src/screen_source/shader.cpp

    # ./src/rendering/
    src/rendering/computeShader.cpp
    src/rendering/imageTexture.cpp
    src/rendering/myCamera.cpp

    # ./thirdparty/
    thirdparty/glad.c

)

# Add include subdirectories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

# Add GLFW
include(FetchContent)

FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG origin/master
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_MakeAvailable(glfw)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# Add GLM
include(FetchContent)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	8d1fd52e5ab5590e2c81768ace50c72bae28f2ed #refs/tags/1.0.1
)

if(NOT glm_POPULATED)
    FetchContent_MakeAvailable(glm)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

# Define assets root so the program knows where to find shaders and textures
target_compile_definitions(${PROJECT_NAME} PRIVATE
    ASSET_DIR="${CMAKE_SOURCE_DIR}/assets/"
)