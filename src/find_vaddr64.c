/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_vaddr64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 07:37:01 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/28 18:58:26 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "return_codes.h"
#include "defines.h"
#include "elf.h"

#define IN_RANGE(min, val, max) ((min) <= (val) && (val) < (max))

static int		check_vaddr64(Elf64_Ehdr *file, size_t start, size_t end)
{
	Elf64_Phdr	*phdr;
	size_t		i;
	size_t		end2;


	phdr = PHDRS64(file);
	i = 0;
	while (i < file->e_phnum)
	{
		end2 = phdr->p_vaddr + phdr->p_memsz;
		if (IN_RANGE(phdr->p_vaddr, start, end2) ||
			IN_RANGE(phdr->p_vaddr, end, end2) ||
			IN_RANGE(start, phdr->p_vaddr, end))
			return (0);
		phdr++;
		i++;
	}
	return (1);
}

static size_t	get_offset(size_t end_of_file, size_t vaddr, size_t align)
{
	size_t		res;

	res = vaddr % align;
	while (res < end_of_file)
		res += align;
	return (res);
}

int				find_vaddr_and_offset64(Elf64_Ehdr *file,
					size_t used_sz, size_t total_sz,
					Elf64_Phdr *loader)
{
	Elf64_Phdr	*phdr;
	size_t		i;
	size_t		start;
	size_t		end;
//	size_t		offset;

	phdr = PHDRS64(file);
	i = 0;
	while (i < file->e_phnum)
	{
		start = (phdr->p_vaddr / phdr->p_align) * phdr->p_align;
		start += loader->p_offset;
		end = start + loader->p_memsz;
		if (phdr->p_type == PT_LOAD &&
			check_vaddr64(file, start, end))
		{
//			offset = get_offset(used_sz, start, phdr->p_align);
//			if ((offset + loader->p_filesz) < total_sz)
//			{
//				loader->p_offset = offset;
				loader->p_vaddr = start;
				loader->p_align = phdr->p_align;
				return (OK);
//			}
		}
		phdr++;
		i++;
	}
	return (WTF);
}


