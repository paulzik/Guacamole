cmake_minimum_required(VERSION 3.16)
project(CustomEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------
# External library paths
# ---------------------------------------------------------
set(SDL3_DIR "${CMAKE_SOURCE_DIR}/external/SDL3-3.2.26")
set(GLEW_DIR "${CMAKE_SOURCE_DIR}/external/glew-2.2.0")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/external/imgui")

# ---------------------------------------------------------
# Debug checks
# ---------------------------------------------------------
message(STATUS "Checking SDL3 LIB: ${SDL3_DIR}/lib/x64/SDL3.lib")

if(NOT EXISTS "${SDL3_DIR}/lib/x64/SDL3.lib")
    message(FATAL_ERROR "SDL3 LIB NOT FOUND at ${SDL3_DIR}/lib/x64/SDL3.lib")
endif()

message(STATUS "SDL3 LIB FOUND!")

# ---------------------------------------------------------
# Include directories
# ---------------------------------------------------------
include_directories(
    "${SDL3_DIR}/include"
    "${GLEW_DIR}/include"
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends"
    "${CMAKE_SOURCE_DIR}/external/glm"
    "${CMAKE_SOURCE_DIR}/src"
)

# ---------------------------------------------------------
# Automatically collect engine source files
# ---------------------------------------------------------
file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

# ---------------------------------------------------------
# ImGui sources
# ---------------------------------------------------------
set(IMGUI_SOURCES
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)

# ---------------------------------------------------------
# Executable - MUST come before custom commands
# ---------------------------------------------------------
add_executable(CustomEngine
    main.cpp
    ${ENGINE_SOURCES}
    ${IMGUI_SOURCES}
)

# ---------------------------------------------------------
# Link directories
# ---------------------------------------------------------
link_directories(
    "${SDL3_DIR}/lib/x64"
    "${GLEW_DIR}/lib/Release/x64"
)

# ---------------------------------------------------------
# Link libraries
# ---------------------------------------------------------
target_link_libraries(CustomEngine PRIVATE
    "${SDL3_DIR}/lib/x64/SDL3.lib"
    "${GLEW_DIR}/lib/Release/x64/glew32.lib"
    opengl32
)

# ---------------------------------------------------------
# Copy shaders after build (no separate project!)
# ---------------------------------------------------------
add_custom_command(TARGET CustomEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/Shaders"
        "${CMAKE_BINARY_DIR}/Shaders"
    COMMENT "Copying shaders to build directory"
)

# ---------------------------------------------------------
# Copy required DLLs after build
# ---------------------------------------------------------
add_custom_command(TARGET CustomEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_DIR}/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:CustomEngine>
)

add_custom_command(TARGET CustomEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GLEW_DIR}/bin/Release/x64/glew32.dll"
        $<TARGET_FILE_DIR:CustomEngine>
)

# ---------------------------------------------------------
# Set working directory (Visual Studio)
# ---------------------------------------------------------
set_property(TARGET CustomEngine PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
