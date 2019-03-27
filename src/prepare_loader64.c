/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_loader64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a.dzykovskyi <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 07:46:50 by a.dzykovskyi      #+#    #+#             */
/*   Updated: 2019/03/26 12:34:19 by a.dzykovskyi     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elf.h"
#include "return_codes.h"
#include "defines.h"
#include "woody.h"

static int		write_old_entrypoint(void *loader, uint32_t old_entrypoint)
{
	void		*sym;
	uint32_t	*arg;

	if (!(sym = find_symbol_by_name64(loader, "jumpaddr")))
		return (WTF);
	arg = (uint32_t*)(sym + 1);
//	*arg = old_entrypoint;
	return (OK);
}

int				prepare_loader64(t_workspace *wsp)
{
	uint32_t	old_entrypoint;

	old_entrypoint = (uint32_t)((Elf64_Ehdr*)wsp->input)->e_entry;
	if (write_old_entrypoint(wsp->loader, old_entrypoint))
		return (WTF);
	return (OK);
}
