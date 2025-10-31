cmake_minimum_required(VERSION 3.20.0)

set(BOARD_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(BOARD atlas)
set(DTC_OVERLAY_FILE ${CMAKE_CURRENT_LIST_DIR}/boards/aesir/atlas/atlas.overlay)

find_package(Zephyr)
project(atlas)


target_sources(app PRIVATE src/test.c)
