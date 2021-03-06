/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a.dzykovskyi <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:19:54 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/26 11:55:08 by a.dzykovskyi     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "woody.h"

int		main(int argc, char **argv)
{
	t_workspace		workspace;

	if (argc != 2)
	{
		write(1, "Usage: woody_woodpacker <file>\n", 31);
		return (1);
	}
	if (check_and_prepare(argv[1], &workspace))
	{
		write(1, "Check fail!\n", 12);
		return (1);
	}
	if (modify_elf64(&workspace))
	{
		write(1, "Fail!\n", 6);
		return (1);
	}
	return (0);
}
