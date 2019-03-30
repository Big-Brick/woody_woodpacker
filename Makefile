NAME1 = woody_woodpacker
NAME2 = loader

CC = gcc
CFLAGS = -Wall -Werror -Wextra -fPIC

ASM = nasm
AFLAGS = -f elf64

LD = ld
LDFLAGS =

INC = includes

SDIR = src

SRCS1 =	\
	main.c \
	check_and_prepare.c \
	get_section64.c \
	find_symbol64.c \
	prepare_loader64.c \
	modify_elf64.c \
	insert_loader64.c \
	find_vaddr64.c \
	xxtea_encrypt.c \
	handling.c \
	offset_into_vaddr64.c

SRCS1_R = $(SRCS1:%.c=$(SDIR)/%.c)

SRCS2 =	\
	loader.asm \
	xxtea_decrypt.c

SRCS2_R = $(SRCS2:%=$(SDIR)/%)

HEADERS1 = \
			defines.h \
			elf.h \
			return_codes.h \
			woody.h \

HEADERS1_R = $(HEADERS1:%.h=$(INC)/%.h)

ODIR = Objects

OBJ1 = $(SRCS1:.c=.o)

OBJ1_R = $(OBJ1:%.o=$(ODIR)/%.o)

OBJ2_T = $(SRCS2:%.c=%.o)

OBJ2 = $(OBJ2_T:%.asm=%.o)

OBJ2_R = $(OBJ2:%.o=$(ODIR)/%.o)

all : $(NAME1)

$(NAME1) : $(ODIR)/ $(OBJ1_R)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME1) $(OBJ1_R) libft/libft.a

$(NAME2) : $(ODIR)/ $(OBJ2_R)
	$(LD) -o $(NAME2) $(OBJ2_R)

.PHONY: clean1 fclean1 dfclean1 re1 clean fclean re

clean1 :
	rm -f $(OBJ1_R)

fclean1 : clean1
	rm -f $(NAME1)

re1 : fclean1 $(NAME1)

clean: clean1

fclean : fclean1
	make fclean -C Libs/libft

re : re1

norm:
	make norm -C libft
	norminette $(SRCS1_R) $(HEADERS1_R)

add:
	make add -C libft
	git add $(SRCS1_R) $(HEADERS1_R)\
			$(SRCS2_R) \
			.gitignore Makefile CMakeLists.txt author

$(ODIR)/ :
	mkdir -p $@

$(ODIR)/%.o : $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I libft/Includes -I $(INC)

$(ODIR)/%.o : $(SDIR)/%.asm
	$(ASM) $(AFLAGS) -o $@ $<
