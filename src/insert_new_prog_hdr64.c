/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_new_prog_hdr64.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a.dzykovskyi <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:56:57 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/27 11:37:14 by a.dzykovskyi     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "return_codes.h"
#include "defines.h"
#include "elf.h"
#include "woody.h"

static int		update_prog_hdrs64(Elf64_Ehdr *file, size_t pos, size_t size)
{
	Elf64_Phdr	*phdrs;
	size_t		i;

	phdrs = (void*)file + file->e_phoff;
	i = 0;
	while (i < file->e_phnum)
	{
		if (pos <= phdrs->p_offset)
			phdrs->p_offset += size;
//		else if (pos < (phdrs->p_offset + phdrs->p_filesz))
//		{
//			phdrs->p_filesz += size;
//			phdrs->p_memsz += size;
//		}
		phdrs++;
		i++;
	}
	return (OK);
}

static int		update_sect_hdrs64(Elf64_Ehdr *file, size_t pos, size_t size)
{
	Elf64_Shdr	*shdrs;
	size_t		i;

	shdrs = (void*)file + file->e_shoff;
	i = 0;
	while (i < file->e_shnum)
	{
		if (pos <= shdrs->sh_offset)
			shdrs->sh_offset += size;
		else if (pos < (shdrs->sh_offset + shdrs->sh_size))
			shdrs->sh_size += size;
		shdrs++;
		i++;
	}
	return (OK);
}

static int		update_elf_hdr64(Elf64_Ehdr *file, size_t pos, size_t size)
{
	if (pos <= file->e_phoff)
		file->e_phoff += size;
	if (pos <= file->e_shoff)
		file->e_shoff += size;
	return (OK);
}

int				insert_new_prog_hdr64(Elf64_Ehdr *file, size_t size)
{
	size_t		insert_pos;
	size_t		insert_size;
	void		*dst;
	void		*src;

	insert_pos = file->e_phoff + file->e_phnum*sizeof(Elf64_Phdr);
	insert_size = sizeof(Elf64_Phdr);
//	insert_pos = 64;
//	insert_size = 64;
	if (update_prog_hdrs64(file, insert_pos, insert_size))
		return (WTF);
//	if (update_sect_hdrs64(file, insert_pos, insert_size))
//		return (WTF);
//	if (update_elf_hdr64(file, insert_pos, insert_size))
//		return (WTF);
//	file->e_phnum++;
	dst = (void*)file + insert_pos + insert_size;
	src = (void*)file + insert_pos;
	memmove(dst, src, size - (insert_pos + insert_size));
//	memmove(src, dst, size - (insert_pos + insert_size));
	return (OK);
}
