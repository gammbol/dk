cmake_minimum_required(VERSION 3.25)

project(ogl VERSION 0.1)

add_subdirectory("include/glfw")
add_subdirectory("include/glad")

add_executable(oglg main.cpp)

target_include_directories(oglg 
    PUBLIC "${PROJECT_SOURCE_DIR}/include/glfw/include"
    PUBLIC "${PROJECT_SOURCE_DIR}/include/glad/include"
)
target_link_libraries(oglg PUBLIC glfw glad)