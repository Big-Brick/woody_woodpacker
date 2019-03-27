/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_prepare.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a.dzykovskyi <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:31:02 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/26 12:10:48 by a.dzykovskyi     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/fcntl.h>

#include "return_codes.h"
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

static int			prepare_file(char *filename, void **res, int prot, size_t *size)
{
	int				fd;
	struct stat		buff;


	if (( fd = open(filename, O_RDWR)) < 0)
		ERROR_RETURN(-1)
	if (fstat(fd, &buff))
		ERROR_RETURN(fd)
	if (buff.st_size <= 0)
	{
		write(1, "Bad file!\n", 10);
		close(fd);
		return (WTF);
	}
	if (MMAP(*res, (size_t)buff.st_size, prot, MAP_SHARED, fd))
		ERROR_RETURN(fd);
	*size = (size_t)buff.st_size;
	close(fd);
	return (OK);
}

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

int					check_and_prepare(char *filename, t_workspace *wsp)
{
	if (filename == NULL || wsp == NULL)
		return (WTF);
	if (prepare_file(filename, &wsp->input, PROT_READ, &wsp->input_size))
		return (WTF);
	if (prepare_file(LOADER_NAME, &wsp->loader, PROT_READ | PROT_WRITE, &wsp->loader_size))
		return (WTF);
	if (prepare_output(wsp, wsp->input_size + wsp->loader_size))
		return (WTF);
	return (check_input_file(wsp->input, wsp->input_size));
}
