
cmake_minimum_required(VERSION 3.13)
project(woody_woodpacker)

set(GRAPHVIZ_GRAPH_NAME          deps)
set(GRAPHVIZ_GENERATE_PER_TARGET OFF)
set(GRAPHVIZ_GENERATE_DEPENDERS  OFF)
set(GRAPHVIZ_IGNORE_TARGETS )

add_executable(woody_woodpacker)

target_include_directories(woody_woodpacker
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/includes
)

target_sources(woody_woodpacker
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/includes/elf.h

    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/main.c
)