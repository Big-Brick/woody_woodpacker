/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_segments64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:44:19 by adzikovs          #+#    #+#             */
/*   Updated: 2019/05/14 08:49:59 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "elf.h"
#include "defines.h"

void				move_sections64(void *file, size_t ins_offset, size_t ins_size)
{
	Elf64_Shdr		*shdr;
	size_t			i;

	shdr = SECT_HDRS64(file);
	i = 0;
	while (i < SHNUM(file))
	{
		if (ins_offset <= shdr->sh_offset)
		{
			shdr->sh_offset += ins_size;
//			shdr->sh_addr += ins_size;
		}
		else if (ins_offset < (shdr->sh_offset + shdr->sh_size))
		{
			shdr->sh_size += ins_size;
		}
		shdr++;
		i++;
	}
}

void				move_segments64(void *file, size_t ins_offset, size_t ins_size)
{
	Elf64_Phdr		*phdr;
	size_t			i;

	phdr = PHDRS64(file);
	i = 0;
	while (i < PHNUM64(file))
	{
		if (ins_offset <= phdr->p_offset)
		{
			phdr->p_offset += ins_size;
//			if (phdr->p_type == PT_LOAD)
//				phdr->p_vaddr += ins_size;
		}
/*		else if (ins_offset < (phdr->p_offset + phdr->p_filesz))
		{
			phdr->p_filesz += ins_size;
			if (phdr->p_memsz)
				phdr->p_memsz += ins_size;
		}*/
		phdr++;
		i++;
	}
}
