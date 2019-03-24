cmake_minimum_required(VERSION 3.13)
project(woody_woodpacker LANGUAGES C ASM_NASM)

add_subdirectory(libft)

set(GRAPHVIZ_GRAPH_NAME          deps)
set(GRAPHVIZ_GENERATE_PER_TARGET OFF)
set(GRAPHVIZ_GENERATE_DEPENDERS  OFF)
set(GRAPHVIZ_IGNORE_TARGETS )

set(CMAKE_VERBOSE_MAKEFILE ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(SRCS src/main.c src/check_and_prepare.c src/copy_segments.c src/check_input_file.c)

add_executable(woody_woodpacker ${SRCS})

target_include_directories(woody_woodpacker
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/includes
        ${LIBFT_INC}
)

target_link_libraries(woody_woodpacker libft.a)

add_custom_command(OUTPUT loader.o
	COMMAND ${CMAKE_ASM_NASM_COMPILER} -f elf64 -o ${CMAKE_CURRENT_SOURCE_DIR}/loader.o ${CMAKE_CURRENT_SOURCE_DIR}/src/loader.asm)

add_custom_target(loader DEPENDS loader.o)
