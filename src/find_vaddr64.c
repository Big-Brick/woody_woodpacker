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

int				find_vaddr_and_offset64(Elf64_Ehdr *file,
					Elf64_Phdr *loader)
{
	Elf64_Phdr	*phdr;
	size_t		i;
	size_t		start;
	size_t		end;

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
			loader->p_vaddr = start;
			loader->p_align = phdr->p_align;
			return (OK);
		}
		phdr++;
		i++;
	}
	return (WTF);
}


