cmake_minimum_required(VERSION 3.5)

project(Loader CXX ASM_MASM)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

# Fetch modules
message("\nFetching modules")
include(cmake/json.cmake)
include(cmake/pugixml.cmake)
include(cmake/cpr.cmake)
include(cmake/imgui.cmake)

# blade
message(STATUS "Loader")
file(GLOB_RECURSE SRC_MAIN
    "${SRC_DIR}/**.hpp"
    "${SRC_DIR}/**.h"
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/**.cc"
    "${SRC_DIR}/**.cxx"
    "${SRC_DIR}/**.asm"
)

add_executable(Loader "${SRC_MAIN}" resources/Loader.rc)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET Loader PROPERTY CXX_STANDARD 23)

source_group(TREE ${SRC_DIR} PREFIX "src" FILES ${SRC_MAIN} )

target_include_directories(Loader PRIVATE 
    "${SRC_DIR}"
    "${json_SOURCE_DIR}/single_include"
    "${imgui_SOURCE_DIR}"
)

target_precompile_headers(Loader PRIVATE "${SRC_DIR}/common.hpp")
target_link_libraries(Loader PRIVATE pugixml d3d11 imgui cpr d3dcompiler nlohmann_json::nlohmann_json dwmapi winmm psapi)

add_compile_definitions(Loader 
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX"
    "WIN32_LEAN_AND_MEAN"
    "_WIN32_WINNT=0x0600"
)