/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:27:13 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/26 19:59:08 by adzikovs         ###   ########.fr       */
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

void				*get_section_by_index64(void *file, unsigned index, char res);

void				*get_section_by_name64(void *file, const char *name, char res);

void				*find_symbol_by_name64(void *file, const char *name);

int					prepare_loader64(t_workspace *wsp);

int					copy_segments_and_headers64(t_workspace *wsp);

int					add_new_segment64(t_workspace *wsp);

int					insert_new_prog_hdr64(Elf64_Ehdr *file, size_t size);

size_t				copy_loader64(void *dst, void *loader);

int					insert_loader64(t_workspace *wsp);

int					modify_elf64(t_workspace *wsp);

#endif
