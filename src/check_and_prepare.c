/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_prepare.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:31:02 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/29 17:37:26 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <string.h>
#include <errno.h>

#include "return_codes.h"
#include "defines.h"
#include "woody.h"

#define ERROR_RETURN(fd) \
	{ \
		perror(NULL); \
		if (fd >= 0) \
			close(fd); \
		return (WTF); \
	}

#define MMAP(res, size, prot, flags, fd) \
	(res = mmap(NULL, size, prot, flags, fd, 0)) == MAP_FAILED

#define P755 \
	S_IRWXU | \
	S_IRGRP | S_IXGRP | \
	S_IROTH | S_IXOTH

static int			prepare_output(t_workspace *wsp, size_t size)
{
	int				fd;
	size_t			i;
	char			buff;

	if ((fd = open(EXEC_NAME, O_RDWR | O_CREAT | O_TRUNC, P755)) < 0)
	{
		perror("unable to open output file: ");
		return (WTF);
	}
	buff = 0;
	i = 0;
	while (i < size)
	{
		if (write(fd, &buff, 1) < 0)
			ERROR_RETURN(fd)
		i++;
	}
	if (MMAP(wsp->res, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd))
		ERROR_RETURN(fd)
	wsp->res_size = size;
	close(fd);
	return (OK);
}

static void error(const char *err, const char *err_str) {

	if (err && err_str)
		fprintf(stderr, "woody: %s: %s\n", err, err_str);
	else if (err)
		fprintf(stderr, "woody: %s\n", err);

	exit(EXIT_FAILURE);
}

static void file_type_validation(const char *filename, void *ptr, size_t size) {

	Elf64_Ehdr *header = ptr;

	if (size < sizeof(Elf64_Ehdr))
		error(filename, "file too small");

	if (header->e_ident[EI_MAG0] != ELFMAG0 || header->e_ident[EI_MAG1] != ELFMAG1 ||
		header->e_ident[EI_MAG2] != ELFMAG2 || header->e_ident[EI_MAG3] != ELFMAG3)
		error(filename, "wrong file type, only ELF files are allowed");

	if (header->e_ident[EI_CLASS] != ELFCLASS64)
		error(filename, "wrong file type, only 64-bit ELF files are allowed");

	if (header->e_ident[EI_DATA] != ELFDATA2LSB)
		error(filename, "wrong file type, only little endian encoded ELF files are allowed");

	if (header->e_ident[EI_VERSION] != EV_CURRENT)
		error(filename, "wrong ELF file version");

	if (header->e_type != ET_EXEC)
		error(filename, "wrong file type, executable file expected");

	if (header->e_machine != EM_X86_64)
		error(filename, "wrong file type, only ELF files for AMD x86-64 are allowed");

	if (header->e_shstrndx >= header->e_shnum)
		error(filename, "wrong string table index");
}

static void file_size_validation(const char *filename, void *ptr, size_t size) {

	Elf64_Ehdr *header = ptr;
	Elf64_Shdr *sheader;
	Elf64_Phdr *pheader;

	if (size < sizeof(Elf64_Ehdr))
		error(filename, "file too small");

	sheader = ptr + header->e_shoff;
	pheader = ptr + header->e_phoff;

	if ((header->e_shnum && size < (size_t)((void *)&sheader[header->e_shnum] - ptr)) || \
		(header->e_phnum && size < (size_t)((void *)&pheader[header->e_shnum] - ptr)))
		error(filename, "file is corrupted");

	if (size < (size_t)((void *)&sheader[header->e_shnum] - ptr) || \
		size < (size_t)((void *)&pheader[header->e_phnum] - ptr))
		error(filename, "file is corrupted");

	sheader = &sheader[header->e_shnum - 1];
	pheader = &pheader[header->e_phnum - 1];

	if (size < sheader->sh_offset + sheader->sh_size || \
		size < pheader->p_offset  + pheader->p_filesz)
		error(filename, "file is corrupted");
}

static void init(const char *filename, void **ptr, size_t *size) {

	int fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		error(filename, strerror(errno));

	if ((*size = lseek(fd, 0, SEEK_END)) == (size_t)-1)
		error("lseek()", strerror(errno));

	if ((*ptr = mmap(0, *size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		error("mmap()", strerror(errno));

	close(fd);

	file_type_validation(filename, *ptr, *size);
	file_size_validation(filename, *ptr, *size);
}

int					check_and_prepare(char *filename, t_workspace *wsp)
{
	size_t			size;

	conf_handling();
	if (filename == NULL || wsp == NULL)
		return (WTF);
	init(filename, &wsp->input, &wsp->input_size);
	init(LOADER_NAME, &wsp->loader, &wsp->loader_size);
	size = copy_loader64(NULL, wsp->loader);
	if (size == 0)
		size = wsp->loader_size;
	if (prepare_output(wsp, wsp->input_size + size))
		return (WTF);
	return (OK);
}
