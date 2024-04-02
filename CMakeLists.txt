cmake_minimum_required(VERSION 3.16)


# Install CPM.cmake
set(CPM_VERSION 0.38.7)
set(CPM_SOURCE_CACHE ${CMAKE_SOURCE_DIR}/ext)
set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_VERSION}/CPM.cmake
            ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})




# Configure Project
project(raylib_main VERSION 0.0.1 LANGUAGES C CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Build Game Executable
add_executable(raylib_main main.cpp)

if(NOT DEFINED ${PLATFORM})
    set(PLATFORM Desktop)
endif()

# Link with Raylib
CPMAddPackage(NAME raylib 
    GITHUB_REPOSITORY raysan5/raylib 
    GIT_TAG 5.0 
    OPTIONS "PLATFORM ${PLATFORM}" "CMAKE_BUILD_TYPE MinSizeRel"
)

target_include_directories(raylib_main PRIVATE ${raylib_SOURCE_DIR}/src)
target_link_libraries(raylib_main PRIVATE raylib)

