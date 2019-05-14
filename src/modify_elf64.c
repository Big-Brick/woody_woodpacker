/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_elf64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:44:53 by a.dzykovskyi      #+#    #+#             */
/*   Updated: 2019/05/14 08:55:34 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "return_codes.h"
#include "defines.h"
#include "elf.h"
#include "woody.h"

int					modify_elf64(t_workspace *wsp)
{
	Elf64_Shdr	*text;
	char		*key;

	key = "1234567890abcdef";
	ft_memcpy(wsp->res, wsp->input, wsp->input_size);
//	if (prepare_loader64(wsp))
//		return (WTF);
//	if (replace_note_segment_on_loader64(wsp))
//		return (WTF);
	if (!(text = get_section_by_name64(wsp->res, ".text", HDR)))
		return (WTF);
	xxtea_encrypt(wsp->res + text->sh_offset, text->sh_size / 4, (const uint32_t*)key);
	if (text_injection64(wsp))
		return (WTF);
	return (OK);
}
