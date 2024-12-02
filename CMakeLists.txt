cmake_minimum_required(VERSION 3.25)

project(dungeonKnight VERSION 0.1)

add_subdirectory("include/glfw")
add_subdirectory("include/glad")
add_subdirectory("include/shaders")
add_subdirectory("include/stb_image")

add_executable(dk src/dk.cpp)

target_include_directories(dk
    PUBLIC "include/glfw/include"
    PUBLIC "include/glad/include"
    PUBLIC "include/shaders/include"
    PUBLIC "include/stb_image/include"
)
target_link_libraries(dk PUBLIC glfw glad shaders stb_image)

file(COPY src/shaders/vertex.glsl DESTINATION shaders/)
file(COPY src/shaders/fragment.glsl DESTINATION shaders/)
file(COPY src/images/wall.jpg DESTINATION images/)
