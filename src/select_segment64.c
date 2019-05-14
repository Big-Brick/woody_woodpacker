/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_segment64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:25:29 by adzikovs          #+#    #+#             */
/*   Updated: 2019/05/14 07:25:29 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elf.h"
#include "woody.h"
#include "defines.h"

Elf64_Phdr			*select_segment64(void *file)
{
	Elf64_Phdr		*phdr;
	size_t			i;

	phdr = PHDRS64(file);
	i = 0;
	while (i < PHNUM64(file))
	{
		if (phdr->p_type == PT_LOAD &&
			(phdr->p_flags & PF_X) &&
			(phdr->p_flags & PF_R))
			return (phdr);
		phdr++;
		i++;
	}
	return (NULL);
}
