cmake_minimum_required(VERSION 3.16)
project(CustomEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------
# Third-party library paths
# ------------------------------
set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/ThirdParty")
set(SDL3_DIR "${THIRDPARTY_DIR}/SDL3")
set(MINIMP3_DIR "${THIRDPARTY_DIR}/minimp3")
set(GLEW_DIR "${THIRDPARTY_DIR}/glew")
set(GLM_DIR  "${THIRDPARTY_DIR}/glm")
set(IMGUI_DIR "${THIRDPARTY_DIR}/imgui")
set(OPENAL_DIR "${THIRDPARTY_DIR}/OpenAL")

# ------------------------------
# Include directories
# ------------------------------
include_directories(
    "${SDL3_DIR}/include"
    "${GLEW_DIR}/include"
    "${GLM_DIR}"
    "${IMGUI_DIR}"
    "${MINIMP3_DIR}"
    "${IMGUI_DIR}/backends"
    "${OPENAL_DIR}/include"
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
    "${MINIMP3_DIR}/minimp3_impl.cpp"
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
# Bullet Physics options
# ------------------------------
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_BULLET3 OFF CACHE BOOL "" FORCE)
set(BUILD_EXTRAS OFF CACHE BOOL "" FORCE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_CPU_DEMOS OFF CACHE BOOL "" FORCE)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(USE_DOUBLE_PRECISION OFF CACHE BOOL "" FORCE)

add_subdirectory(ThirdParty/bullet3 EXCLUDE_FROM_ALL)

include_directories(
    "${THIRDPARTY_DIR}/bullet3/src"
)

# Include OpenAL headers
include_directories("${OPENAL_DIR}/include")

# ------------------------------
# Link directories for SDL, GLEW, OpenAL
# ------------------------------
link_directories(
    "${SDL3_DIR}/lib/x64"
    "${GLEW_DIR}/lib/Release/x64"
    "${OPENAL_DIR}/lib"
)

# --- Assimp options ---
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(ThirdParty/assimp EXCLUDE_FROM_ALL)


# ------------------------------
# Linking
# ------------------------------
target_link_libraries(CustomEngine PRIVATE
    ImGui
    "${SDL3_DIR}/lib/x64/SDL3.lib"
    "${GLEW_DIR}/lib/Release/x64/glew32.lib"
    "${OPENAL_DIR}/lib/OpenAL32.lib"
    opengl32
    assimp

    BulletDynamics
    BulletCollision
    LinearMath
)

set_target_properties(BulletCollision PROPERTIES FOLDER "ThirdParty/Bullet")
set_target_properties(BulletDynamics PROPERTIES FOLDER "ThirdParty/Bullet")
set_target_properties(LinearMath PROPERTIES FOLDER "ThirdParty/Bullet")

# ------------------------------
# Copy runtime DLLs next to the executable after build
# ------------------------------
set(DLLS_TO_COPY
    "${SDL3_DIR}/lib/x64/SDL3.dll"
    "${GLEW_DIR}/bin/Release/x64/glew32.dll"
    "${OPENAL_DIR}/bin/OpenAL32.dll"
)

foreach(dll ${DLLS_TO_COPY})
    if(EXISTS ${dll})
        add_custom_command(TARGET CustomEngine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${dll}"
                $<TARGET_FILE_DIR:CustomEngine>
        )
    else()
        message(WARNING "DLL not found, skipping copy: ${dll}")
    endif()
endforeach()
# ------------------------------
# Set working directory for VS debugger
# ------------------------------
set_property(TARGET CustomEngine PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
