cmake_minimum_required(VERSION 3.15)
project(metaballs)

set(CMAKE_CXX_STANDARD 14)

add_executable(metaballs main.cpp shader.cpp shader.h circle.cpp circle.h grid.cpp grid.h cell.cpp cell.h)

target_link_libraries(metaballs glfw3)
target_link_libraries(metaballs GLEW)
target_link_libraries(metaballs GL)
target_link_libraries(metaballs X11)
target_link_libraries(metaballs dl)
target_link_libraries(metaballs pthread)