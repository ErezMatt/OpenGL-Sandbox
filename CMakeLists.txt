cmake_minimum_required(VERSION 3.20)
project(OpenGL-Sandbox)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source directories
set(SCENES_DIR ${CMAKE_SOURCE_DIR}/Scenes)
# Create executable
file(GLOB SOURCES
    *.cpp
    "${SCENES_DIR}/*.cpp"
)
file(GLOB HEADERS 
	*.h
	"${SCENES_DIR}/*.h"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Dependencies
include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# GLEW
FetchContent_Declare(
    GLEW
    GIT_REPOSITORY https://github.com/Perlmint/glew-cmake
    GIT_TAG glew-cmake-2.2.0
)
FetchContent_MakeAvailable(GLEW)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC)
target_include_directories(${PROJECT_NAME} PRIVATE ${glew_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} libglew_static)

#glm
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/icaven/glm.git
    GIT_TAG master
)
FetchContent_MakeAvailable(glm)
target_link_libraries(${PROJECT_NAME} glm)

# ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.89.7-docking
)
FetchContent_MakeAvailable(imgui)
add_library(imgui)
target_include_directories(
	imgui
	PUBLIC
	${imgui_SOURCE_DIR}
	${imgui_SOURCE_DIR}/backends
	)
	
target_sources(
	imgui
	PUBLIC
	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_tables.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
	)
target_link_libraries(imgui PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} imgui)

# stb_image (Single-header library)
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)
FetchContent_MakeAvailable(stb)
target_include_directories(${PROJECT_NAME} PRIVATE ${stb_SOURCE_DIR})

#Assimp
FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG v5.2.5
)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(assimp)
target_include_directories(${PROJECT_NAME} PRIVATE _deps/assimp-src/include)
target_link_libraries(${PROJECT_NAME} assimp)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)


# Include directories
include_directories(${PROJECT_SOURCE_DIR})

