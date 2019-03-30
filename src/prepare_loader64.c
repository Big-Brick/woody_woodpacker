/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_loader64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 07:46:50 by a.dzykovskyi      #+#    #+#             */
/*   Updated: 2019/03/30 11:05:00 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elf.h"
#include "return_codes.h"
#include "defines.h"
#include "woody.h"

static int		write_old_entrypoint(void *loader, uint64_t old_entrypoint)
{
	void		*sym;
	uint64_t	*arg;

	if (!(sym = find_symbol_by_name64(loader, "jumpaddr")))
		return (WTF);
	arg = (uint64_t*)(sym + 2);
	*arg = (uint64_t)old_entrypoint;
	return (OK);
}

int				prepare_loader64(t_workspace *wsp)
{
	uint64_t	old_entrypoint;

	old_entrypoint = ((Elf64_Ehdr*)wsp->input)->e_entry;
	if (write_old_entrypoint(wsp->loader, old_entrypoint))
		return (WTF);
	return (OK);
}
