cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_FLAGS "-std=c++20")

project(dungeonKnight VERSION 0.1)

add_subdirectory("include/glfw")
add_subdirectory("include/glad")
add_subdirectory("include/shaders")
add_subdirectory("include/stb_image")
add_subdirectory("include/glm")

add_executable(dk src/dk.cpp)

target_include_directories(dk
    PUBLIC "include/glfw/include"
    PUBLIC "include/glad/include"
    PUBLIC "include/shaders/include"
    PUBLIC "include/stb_image/include"
)
target_link_libraries(dk PUBLIC glfw glad shaders stb_image glm)

file(COPY src/shaders/vertex.vs DESTINATION shaders/)
file(COPY src/shaders/fragment.fs DESTINATION shaders/)
file(COPY src/shaders/lightFragment.fs DESTINATION shaders/)
file(COPY src/images/wall.jpg DESTINATION images/)
file(COPY src/images/awesomeface.png DESTINATION images/)
