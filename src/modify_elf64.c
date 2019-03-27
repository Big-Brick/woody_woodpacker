/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_elf64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a.dzykovskyi <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:44:53 by a.dzykovskyi      #+#    #+#             */
/*   Updated: 2019/03/27 10:52:56 by a.dzykovskyi     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "return_codes.h"
#include "elf.h"
#include "woody.h"

int					modify_elf64(t_workspace *wsp)
{
	Elf64_Ehdr		*hdr;
	Elf64_Ehdr		*hdr2;

	hdr = wsp->input;
	hdr2 = wsp->res;
	ft_memcpy(wsp->res, wsp->input, wsp->input_size);
//	if (insert_new_prog_hdr64(wsp->res, wsp->res_size))
//		return (WTF);
	if (insert_loader64(wsp))
		return (WTF);
	return (OK);
}
