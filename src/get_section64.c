/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a.dzykovskyi <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:08:04 by a.dzykovskyi      #+#    #+#             */
/*   Updated: 2019/03/26 11:59:28 by a.dzykovskyi     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "defines.h"
#include "elf.h"

#include "libft.h"

void			*get_section_by_index64(void *file, size_t index, char res)
{
	if (index >= ((Elf64_Ehdr*)file)->e_shnum)
		return (NULL);
	if (res == HDR)
		return (SECT_HDRS64(file) + index);
	else
		return (file + SECT_HDRS64(file)[index].sh_offset);
}

void			*get_section_by_name64(void *file, const char *name, char res)
{
	size_t		i;
	Elf64_Shdr	*shstrtable_hdr;
	char		*shstrtable;

	shstrtable_hdr = SECT_HDRS64(file) + ((Elf64_Ehdr*)file)->e_shstrndx;
	shstrtable = (char*)(file + shstrtable_hdr->sh_offset);
	i = 0;
	while (i < ((Elf64_Ehdr*)file)->e_shnum)
	{
		if (ft_strcmp(shstrtable + SECT_HDRS64(file)[i].sh_name, name) == 0)
		{
			if (res == HDR)
				return (SECT_HDRS64(file) + i);
			else
				return (file + SECT_HDRS64(file)[i].sh_offset);
		}
		i++;
	}
	return (NULL);
}
