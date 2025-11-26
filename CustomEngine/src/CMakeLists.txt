cmake_minimum_required(VERSION 3.16)
project(CustomEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------
# Third-party library paths
# ------------------------------
set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/ThirdParty")
set(SDL3_DIR "${THIRDPARTY_DIR}/SDL3")
set(GLEW_DIR "${THIRDPARTY_DIR}/glew")
set(GLM_DIR  "${THIRDPARTY_DIR}/glm")
set(IMGUI_DIR "${THIRDPARTY_DIR}/imgui")

# ------------------------------
# Includes
# ------------------------------
include_directories(
    "${SDL3_DIR}/include"
    "${GLEW_DIR}/include"
    "${GLM_DIR}"
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends"
    "${CMAKE_SOURCE_DIR}/src"
)

# ------------------------------
# Engine sources
# ------------------------------
file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

# ------------------------------
# Executable
# ------------------------------
add_executable(CustomEngine main.cpp ${ENGINE_SOURCES})

# Organize /src correctly in Visual Studio
source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "Source" FILES ${ENGINE_SOURCES})
source_group("" FILES main.cpp)

# ------------------------------
# ImGui as static library
# ------------------------------
add_library(ImGui STATIC
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)

target_include_directories(ImGui PUBLIC
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends"
    "${SDL3_DIR}/include"
    "${GLEW_DIR}/include"
)

set_target_properties(ImGui PROPERTIES FOLDER "ThirdParty")

# ------------------------------
# Link directories
# ------------------------------
link_directories(
    "${SDL3_DIR}/lib/x64"
    "${GLEW_DIR}/lib/Release/x64"
)

# ------------------------------
# Linking
# ------------------------------
target_link_libraries(CustomEngine PRIVATE
    ImGui
    "${SDL3_DIR}/lib/x64/SDL3.lib"
    "${GLEW_DIR}/lib/Release/x64/glew32.lib"
    opengl32
)

# ------------------------------
# Copy shaders after build
# ------------------------------
add_custom_command(TARGET CustomEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/Shaders"
        "${CMAKE_BINARY_DIR}/Shaders"
    COMMENT "Copying shaders to build directory"
)

# ------------------------------
# Copy required DLLs after build
# ------------------------------
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

# ------------------------------
# Set working directory for Visual Studio
# ------------------------------
set_property(TARGET CustomEngine PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
