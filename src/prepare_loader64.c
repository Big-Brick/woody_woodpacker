/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_loader64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 07:46:50 by a.dzykovskyi      #+#    #+#             */
/*   Updated: 2019/03/30 17:23:49 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elf.h"
#include "return_codes.h"
#include "defines.h"
#include "woody.h"

static int		write_old_entrypoint64(void *loader, uint64_t old_entrypoint)
{
	Elf64_Sym	*jumpaddr;
	Elf64_Shdr	*text;
	size_t		offset;
	uint64_t	*arg;

	if (!(jumpaddr = find_symbol_by_name64(loader, "jumpaddr")) ||
		!(text = get_section_by_name64(loader, ".text", HDR)) ||
		jumpaddr->st_value < text->sh_addr)
		return (WTF);
	offset = text->sh_offset + (jumpaddr->st_value - text->sh_addr);
	arg = (uint64_t*)(loader + offset + 2);
	*arg = (uint64_t)old_entrypoint;
	return (OK);
}

static int		write_xxtea_args64(void *loader, Elf64_Addr data, size_t len)
{
	Elf64_Sym	*arg_sym;
	Elf64_Shdr	*text;
	size_t		offset;
	uint64_t	*arg;

	if (!(arg_sym = find_symbol_by_name64(loader, "text_addr")) ||
		!(text = get_section_by_name64(loader, ".text", HDR)) ||
		arg_sym->st_value < text->sh_addr)
		return (WTF);
	offset = text->sh_offset + (arg_sym->st_value - text->sh_addr);
	arg = (uint64_t*)(loader + offset + 2);
	*arg = (uint64_t)data;
	if (!(arg_sym = find_symbol_by_name64(loader, "text_len")) ||
		arg_sym->st_value < text->sh_addr)
		return (WTF);
	offset = text->sh_offset + (arg_sym->st_value - text->sh_addr);
	arg = (uint64_t*)(loader + offset + 2);
	*arg = (uint64_t)len;
	return (OK);
}

int				prepare_loader64(t_workspace *wsp)
{
	uint64_t	old_entrypoint;
	Elf64_Shdr	*text;

	old_entrypoint = ((Elf64_Ehdr*)wsp->input)->e_entry;
	if (write_old_entrypoint64(wsp->loader, old_entrypoint))
		return (WTF);
	if (!(text = get_section_by_name64(wsp->input, ".text", HDR)))
		return (WTF);
	if (write_xxtea_args64(wsp->loader, text->sh_addr, text->sh_size / 4))
		return (WTF);
	return (OK);
}
