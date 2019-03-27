/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_segments64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:37:15 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/26 20:10:07 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "return_codes.h"
#include "elf.h"
#include "woody.h"

static int		copy_header_and_segment64(
					t_workspace *wsp, size_t hdr,
					ssize_t shift_offset, size_t shift_size)
{
	Elf64_Phdr		*in_seg_hdr;
	Elf64_Phdr		*res_seg_hdr;
	void			*in_seg;
	void			*res_seg;

	in_seg_hdr = (Elf64_Phdr*)(wsp->input + hdr);
	res_seg_hdr = (Elf64_Phdr*)(wsp->res + hdr);
	ft_memcpy(res_seg_hdr, in_seg_hdr, sizeof(*in_seg_hdr));
	res_seg_hdr->p_offset += shift_size;
	in_seg = wsp->input + in_seg_hdr->p_offset;
	res_seg = wsp->res + res_seg_hdr->p_offset;
	ft_memcpy(res_seg, in_seg, in_seg_hdr->p_filesz);
	return (OK);
}

int				copy_segments_and_headers64(t_workspace *wsp)
{
	Elf64_Ehdr	*hdr;
	size_t		seg_hdr_off;
	size_t		i;

	hdr = (Elf64_Ehdr*)wsp->input;
	seg_hdr_off = (size_t)(hdr->e_phoff);
	i = 0;
	while (i < hdr->e_phnum)
	{
//		if (copy_header_and_segment64(wsp, seg_hdr_off, sizeof(Elf64_Phdr)))
//			return (WTF);
		seg_hdr_off += sizeof(Elf64_Phdr);
		i++;
	}
	return (OK);
}
