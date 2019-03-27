/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_segment64.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a.dzykovskyi <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:17:52 by a.dzykovskyi      #+#    #+#             */
/*   Updated: 2019/03/26 13:32:06 by a.dzykovskyi     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "return_codes.h"
#include "defines.h"
#include "elf.h"
#include "woody.h"

int				add_new_segment64(t_workspace *wsp)
{
	Elf64_Ehdr	*hdr;
	Elf64_Phdr	*new_seg_hdr;
	void		*new_seg;


	hdr = (Elf64_Ehdr*)wsp->res;
	if (prepare_loader64(wsp))
		return (WTF);
	new_seg_hdr = wsp->res + hdr->e_phoff +
		hdr->e_phentsize*hdr->e_phnum;
	new_seg_hdr->p_type = PT_LOAD;
	new_seg_hdr->p_flags = PF_X | PF_R;
	new_seg_hdr->p_offset = wsp->input_size;
	new_seg_hdr->p_vaddr = wsp->input_size;
	new_seg_hdr->p_paddr = new_seg_hdr->p_vaddr;
	new_seg_hdr->p_align = 1;
	new_seg = wsp->res + new_seg_hdr->p_offset;
	new_seg_hdr->p_filesz = copy_loader64(new_seg, wsp->loader);
	if (new_seg_hdr->p_filesz == 0)
		return (WTF);
	new_seg_hdr->p_memsz = new_seg_hdr->p_filesz;
	hdr->e_phnum++;
	return (OK);
}
