cmake_minimum_required(VERSION 3.25)

project(shaders)

add_library(shaders src/shaders.cpp)
target_include_directories(shaders PUBLIC include)

target_link_libraries(shaders PUBLIC glad glm)
add_dependencies(shaders glad glm)
