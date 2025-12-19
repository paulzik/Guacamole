cmake_minimum_required(VERSION 3.16)
project(CustomEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
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
# Include directories
# ------------------------------
include_directories(
    "${SDL3_DIR}/include"
    "${GLEW_DIR}/include"
    "${GLM_DIR}"
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends"
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/Editor"
)

# ------------------------------
# Engine sources (all files in src/)
# ------------------------------
file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

# ------------------------------
# Editor sources (all files in Editor/)
# ------------------------------
file(GLOB_RECURSE EDITOR_SOURCES
    "${CMAKE_SOURCE_DIR}/Editor/*.cpp"
    "${CMAKE_SOURCE_DIR}/Editor/*.h"
)

# ------------------------------
# Executable target
# ------------------------------
add_executable(CustomEngine "${CMAKE_SOURCE_DIR}/main.cpp"
    ${ENGINE_SOURCES}
    ${EDITOR_SOURCES}
)

# ------------------------------
# Visual Studio solution folders mirroring disk
# ------------------------------
source_group(TREE "${CMAKE_SOURCE_DIR}/src" PREFIX "src" FILES ${ENGINE_SOURCES})
source_group(TREE "${CMAKE_SOURCE_DIR}/Editor" PREFIX "Editor" FILES ${EDITOR_SOURCES})
source_group("" FILES "${CMAKE_SOURCE_DIR}/main.cpp")

# ------------------------------
# ImGui static library
# ------------------------------
set(IMGUI_SOURCES
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)

add_library(ImGui STATIC ${IMGUI_SOURCES})

target_include_directories(ImGui PUBLIC
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends"
    "${SDL3_DIR}/include"
    "${GLEW_DIR}/include"
)

set_target_properties(ImGui PROPERTIES FOLDER "ThirdParty")
source_group(TREE "${IMGUI_DIR}" PREFIX "ThirdParty/ImGui" FILES ${IMGUI_SOURCES})

# ------------------------------
# Link directories for SDL and GLEW
# ------------------------------
link_directories(
    "${SDL3_DIR}/lib/x64"
    "${GLEW_DIR}/lib/Release/x64"
)

# --- Assimp options ---
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)     # avoid DLLs
set(ASSIMP_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(ThirdParty/assimp EXCLUDE_FROM_ALL)

# ------------------------------
# Linking
# ------------------------------
target_link_libraries(CustomEngine PRIVATE
    ImGui
    "${SDL3_DIR}/lib/x64/SDL3.lib"
    "${GLEW_DIR}/lib/Release/x64/glew32.lib"
    opengl32
    assimp
)
# ------------------------------
# Copy DLLs after build
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
# Set working directory for VS debugger
# ------------------------------
set_property(TARGET CustomEngine PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
