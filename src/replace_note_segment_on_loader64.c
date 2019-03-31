/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_note_segment_on_loader64.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:20:32 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/31 11:16:57 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "return_codes.h"
#include "defines.h"
#include "elf.h"
#include "woody.h"

size_t			copy_loader64(void *dst, void *loader)
{
	Elf64_Shdr	*text;

	text = get_section_by_name64(loader, ".text", HDR);
	if (dst && text && text->sh_size)
		ft_memcpy(dst, loader + text->sh_offset, text->sh_size);
	return (text->sh_size);
}

static Elf64_Phdr *find_note_segment(Elf64_Ehdr *file)
{
	Elf64_Phdr	*phdr;
	size_t		i;

	phdr = PHDRS64(file);
	i = 0;
	while (i < file->e_phnum)
	{
		if (phdr->p_type == PT_NOTE)
			return (phdr);
		phdr++;
		i++;
	}
	return (NULL);
}

int				replace_note_segment_on_loader64(t_workspace *wsp)
{
	Elf64_Phdr	*loader;

	loader = find_note_segment(wsp->res);
	loader->p_type = PT_LOAD;
	loader->p_flags = PF_X | PF_R;
	loader->p_offset = wsp->input_size;
	loader->p_filesz = copy_loader64(NULL, wsp->loader);
	if (loader->p_filesz == 0)
		return (WTF);
	loader->p_memsz = loader->p_filesz;
	if (find_vaddr_and_offset64(wsp->res, loader))
			return (WTF);
	loader->p_paddr = loader->p_vaddr;
	loader->p_filesz = copy_loader64(wsp->res + loader->p_offset, wsp->loader);
	if (loader->p_filesz == 0)
		return (WTF);
	loader->p_memsz = loader->p_filesz;
	((Elf64_Ehdr*)wsp->res)->e_entry = loader->p_vaddr;
	return (OK);
}
