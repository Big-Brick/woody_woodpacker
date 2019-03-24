/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:40:46 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/24 17:40:46 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>

#include "return_codes.h"
#include "elf.h"

int		check_input_file(void *ptr, size_t size)
{
	Elf64_Ehdr	*hdr;

	if (ptr == NULL)
		return (WTF);
	hdr = ptr;
	if (hdr->e_type != ELFCLASS64)
	{
		write(1, "Only elf64 supported!\n", 22);
		return (WTF);
	}
	return (OK);
}
