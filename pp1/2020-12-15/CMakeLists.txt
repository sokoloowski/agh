cmake_minimum_required(VERSION 3.17)
project(drzewa C)

set(CMAKE_C_STANDARD 11)

add_executable(drzewa drzewa.c)
add_executable(pliki pliki.c)
add_executable(enum enum.c)
add_executable(polabitowe polabitowe.c)