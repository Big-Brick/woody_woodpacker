/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:27:13 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/24 16:46:51 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# include <stdlib.h>

# include "elf.h"

# define EXEC_NAME "woody"
# define LOADER_NAME "loader.o"

typedef struct		s_workspace
{
	void			*input;
	size_t			input_size;
	void			*loader;
	size_t			loader_size;
	void			*res;
	size_t			res_size;
}					t_workspace;

int					check_and_prepare(char *filename, t_workspace *wsp);

int					check_input_file(void *ptr, size_t size);

#endif
