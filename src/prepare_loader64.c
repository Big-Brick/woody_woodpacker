/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_loader64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 07:46:50 by a.dzykovskyi      #+#    #+#             */
/*   Updated: 2019/03/31 12:29:59 by adzikovs         ###   ########.fr       */
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

static int		write_8b_arg64(void *loader, uint64_t arg, size_t opcode_size,
					const char* op_label)
{
	Elf64_Sym	*op_sym;
	Elf64_Shdr	*text;
	size_t		offset;
	uint64_t	*arg_ptr;

	if (!(op_sym = find_symbol_by_name64(loader, op_label)) ||
		!(text = get_section_by_name64(loader, ".text", HDR)) ||
		op_sym->st_value < text->sh_addr)
		return (WTF);
	offset = text->sh_offset + (op_sym->st_value - text->sh_addr);
	arg_ptr = (uint64_t*)(loader + offset + opcode_size);
	*arg_ptr = arg;
	return (OK);
}

static int		write_xxtea_args64(void *loader, Elf64_Addr data, Elf64_Xword len)
{
	if (write_8b_arg64(loader, data, 2, "text_addr"))
		return (WTF);
	if (write_8b_arg64(loader, len, 2, "text_len"))
		return (WTF);
	return (OK);
}

static int		write_mprotect_args64(void *loader, Elf64_Addr addr, Elf64_Xword len)
{
	if (write_8b_arg64(loader, addr, 2, "text_page_addr"))
		return (WTF);
	if (write_8b_arg64(loader, len, 2, "text_page_len"))
		return (WTF);
	return (OK);
}

int				prepare_loader64(t_workspace *wsp)
{
	uint64_t	old_entrypoint;
	Elf64_Shdr	*text;
	Elf64_Addr	addr;
	Elf64_Xword	len;

	old_entrypoint = ((Elf64_Ehdr*)wsp->input)->e_entry;
	if (write_old_entrypoint64(wsp->loader, old_entrypoint))
		return (WTF);
	if (!(text = get_section_by_name64(wsp->res, ".text", HDR)))
		return (WTF);
	addr = (text->sh_addr / 4096) * 4096;
	len = text->sh_addr % 4096 + text->sh_size;
	if (write_mprotect_args64(wsp->loader, addr, len))
		return (WTF);
	if (write_xxtea_args64(wsp->loader, text->sh_addr, text->sh_size / 4))
		return (WTF);
	return (OK);
}
