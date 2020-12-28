cmake_minimum_required(VERSION 3.17)
project(plik C)

set(CMAKE_C_STANDARD 11)
link_libraries(ws2_32 wsock32)

add_executable(klient klient.c)
add_executable(serwer serwer.c)