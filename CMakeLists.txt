cmake_minimum_required(VERSION 3.10)

project(chess C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(chess main.c chess_board/board.c)

target_include_directories(chess PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/chess_board)

target_link_libraries(chess PRIVATE raylib)
