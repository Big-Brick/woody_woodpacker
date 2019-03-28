/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_loader64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:20:32 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/28 19:15:22 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "return_codes.h"
#include "defines.h"
#include "elf.h"
#include "woody.h"

size_t			copy_loader64(void *dst, void *loader)
{
	void		*start;
	void		*end;
	size_t		size;

	start = find_symbol_by_name64(loader, "loader_start");
	end = find_symbol_by_name64(loader, "loader_end");
	if (end <= start)
		return (0);
	size = end - start;
	if (dst && start)
		ft_memcpy(dst, start, size);
	return (size);
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

static size_t	get_vaddr(Elf64_Ehdr *file)
{
	Elf64_Phdr	*phdr;
	size_t		i;
	size_t		res = 0;

	phdr = PHDRS64(file);
	i = 0;
	while (i < file->e_phnum)
	{
		if (phdr->p_type == PT_LOAD &&
			res < (phdr->p_vaddr + phdr->p_memsz))
			res = phdr->p_vaddr + phdr->p_memsz;
		phdr++;
		i++;
	}
	return (res);
}

int				insert_loader64(t_workspace *wsp)
{
	Elf64_Phdr	*loader;
//	Elf64_Phdr	*last_phdr;

	if (prepare_loader64(wsp))
		return (WTF);
//	last_phdr = PHDRS64(wsp->res) + PHNUM64(wsp->res) - 1;
	loader = find_note_segment(wsp->res);
	loader->p_type = PT_LOAD;
	loader->p_flags = PF_X | PF_R;
	loader->p_offset = wsp->input_size;
	loader->p_filesz = copy_loader64(NULL, wsp->loader);
	if (loader->p_filesz == 0)
		return (WTF);
	loader->p_memsz = loader->p_filesz;
	if (find_vaddr_and_offset64(wsp->res,
			wsp->input_size, wsp->res_size, loader))
			return (WTF);
//	loader->p_offset = wsp->input_size;
//	loader->p_vaddr = 0x800000 + loader->p_offset;
					//0x400000
//	loader->p_align = 0x200000;
	loader->p_paddr = loader->p_vaddr;
	loader->p_filesz = copy_loader64(wsp->res + loader->p_offset, wsp->loader);
	if (loader->p_filesz == 0)
		return (WTF);
	loader->p_memsz = loader->p_filesz;
	((Elf64_Ehdr*)wsp->res)->e_entry = loader->p_vaddr;
	return (OK);
}
