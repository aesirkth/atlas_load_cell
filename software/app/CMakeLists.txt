cmake_minimum_required(VERSION 3.20.0)

set(BOARD_ROOT ${CMAKE_CURRENT_LIST_DIR}/..)
set(BOARD atlas)

find_package(Zephyr)
project(atlas)

target_sources(app PRIVATE src/main.c)