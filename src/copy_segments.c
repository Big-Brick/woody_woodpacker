/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_segments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:37:15 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/24 17:55:16 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "return_codes.h"
#include "elf.h"
#include "woody.h"

static int		copy_header_and_segment(t_workspace *workspace, size_t hdr, ssize_t shift)
{
	Elf64_Phdr		*in_seg_hdr;
	Elf64_Phdr		*res_seg_hdr;
	void			*in_seg;
	void			*res_seg;

	in_seg_hdr = (Elf64_Phdr*)(workspace->input + hdr);
	res_seg_hdr = (Elf64_Phdr*)(workspace->res + hdr);
	ft_memcpy(res_seg_hdr, in_seg_hdr, sizeof(*in_seg_hdr));
	res_seg_hdr->p_offset += shift;
	in_seg = workspace->input + in_seg_hdr->p_offset;
	res_seg = workspace->res + res_seg_hdr->p_offset;
	ft_memcpy(res_seg, in_seg, in_seg_hdr->p_filesz);
	return (OK);
}

int				copy_segments_and_headers(t_workspace *workspace)
{
	Elf64_Ehdr	*hdr;

	hdr = (Elf64_Ehdr*)workspace->input;
	return (OK);
}
