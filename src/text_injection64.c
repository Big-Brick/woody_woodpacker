/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_injection64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:21:46 by adzikovs          #+#    #+#             */
/*   Updated: 2019/05/14 08:58:28 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "woody.h"
#include "return_codes.h"

int					text_injection64(t_workspace *wsp)
{
	Elf64_Phdr		*target_segment;
	size_t			insert_pos;
	size_t			insert_size;

	if ((target_segment = select_segment64(wsp->res)) == NULL)
		return (WTF);
	insert_pos = target_segment->p_offset + target_segment->p_filesz;
	insert_size = (size_t)sysconf(_SC_PAGESIZE);
	if (prepare_loader64(wsp))
		return (WTF);
	move_segments64(wsp->res, insert_pos, insert_size);
	move_sections64(wsp->res, insert_pos, insert_size);
	ft_memmove(wsp->res + insert_pos + insert_size,
		wsp->res + insert_pos, wsp->res_size - insert_pos - insert_size);
	copy_loader64(wsp->res + insert_pos, wsp->loader);
	((Elf64_Ehdr*)wsp->res)->e_entry = target_segment->p_vaddr + target_segment->p_memsz;
	target_segment->p_filesz += insert_size;
	target_segment->p_memsz += insert_size;
	if (insert_pos <= ((Elf64_Ehdr*)wsp->res)->e_phoff)
		((Elf64_Ehdr*)wsp->res)->e_phoff += insert_size;
	if (insert_pos <= ((Elf64_Ehdr*)wsp->res)->e_shoff)
		((Elf64_Ehdr*)wsp->res)->e_shoff += insert_size;
	return (OK);
}
