/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_symbol64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a.dzykovskyi <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 07:34:20 by a.dzykovskyi      #+#    #+#             */
/*   Updated: 2019/03/26 13:32:06 by a.dzykovskyi     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "return_codes.h"
#include "defines.h"
#include "elf.h"
#include "woody.h"

void		*find_symbol_by_name64(void *file, const char *name)
{
	Elf64_Shdr	*symtab_hdr;
	Elf64_Sym	*symtab;
	char		*strtab;
	size_t		i;
	size_t		offset;


	symtab_hdr = ((Elf64_Shdr*)get_section_by_name64(file, ".symtab", HDR));
	symtab = (Elf64_Sym*)(file + symtab_hdr->sh_offset);
	strtab = get_section_by_name64(file, ".strtab", SECT);
	i = 0;
	while (((i + 1)*sizeof(*symtab)) <= symtab_hdr->sh_size)
	{
		if (ft_strcmp(strtab + symtab[i].st_name, name) == 0)
		{
			offset = SECT_HDRS64(file)[symtab[i].st_shndx].sh_offset;
			offset += symtab[i].st_value;
			return (file + offset);
		}
		i++;
	}
	return (NULL);
}
