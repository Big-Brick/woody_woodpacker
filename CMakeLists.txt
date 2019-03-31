cmake_minimum_required(VERSION 3.12)
project(woody_woodpacker LANGUAGES C ASM_NASM)

add_subdirectory(libft)

set(GRAPHVIZ_GRAPH_NAME          deps)
set(GRAPHVIZ_GENERATE_PER_TARGET OFF)
set(GRAPHVIZ_GENERATE_DEPENDERS  OFF)
set(GRAPHVIZ_IGNORE_TARGETS )

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(SRCS
	src/main.c
	src/check_and_prepare.c
	src/get_section64.c
	src/find_symbol64.c
	src/prepare_loader64.c
	src/modify_elf64.c
	src/replace_note_segment_on_loader64.c
	src/insert_loader_int_the_end_of_segment64.c
	src/find_vaddr64.c
	src/xxtea_encrypt.c
	src/handling.c)

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

add_custom_command(OUTPUT xxtea_decrypt.o
		COMMAND ${CMAKE_C_COMPILER} -o ${CMAKE_CURRENT_SOURCE_DIR}/xxtea_decrypt.o -c ${CMAKE_CURRENT_SOURCE_DIR}/src/xxtea_decrypt.c)

add_custom_target(decryptor DEPENDS xxtea_decrypt.o)
