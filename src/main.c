/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:19:54 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/24 17:26:23 by adzikovs         ###   ########.fr       */
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
	check_and_prepare(argv[1], &workspace);
	return (0);
}
