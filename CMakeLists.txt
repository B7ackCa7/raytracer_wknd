cmake_minimum_required(VERSION 3.23)

project(raytracer_weekend)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Add header files 
file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/*.h
    $CMAKE_SOURCE_DIR}/src/*.hpp)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# define the include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
