cmake_minimum_required(VERSION 3.17)
project(2021-01-05 C)

set(CMAKE_C_STANDARD 11)
link_libraries(opengl32)
link_libraries(glu32)
link_libraries(gdi32)

add_executable(main main.c)