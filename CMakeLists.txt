cmake_minimum_required(VERSION 3.11)
project(RaycastEngine)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)

if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_SHARED_LIBS OFF)  # Build static libraries
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Our Project
add_executable(${PROJECT_NAME} main.cpp
        data/Constants.h
        data/Map.h
        data/Map.cpp
        data/Map1.h
        data/Map1.cpp
        engine/EngineUtils.h
        engine/Player.h
        engine/Player.cpp
        engine/Renderer.h
        engine/Renderer.cpp)

# Static linking options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libstdc++ -static-libgcc")

target_link_libraries(${PROJECT_NAME} raylib)

# Additional configurations (e.g., for Web, Mac)
