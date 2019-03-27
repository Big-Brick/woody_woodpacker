/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:19:13 by a.dzykovskyi      #+#    #+#             */
/*   Updated: 2019/03/26 19:20:28 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODPACKER_DEFINES_H
# define WOODPACKER_DEFINES_H

# define HDR 0
# define SECT 1

# define PHNUM64(p) (((Elf64_Ehdr*)p)->e_phnum)
# define PHDRS64(p) ((Elf64_Phdr*)((void*)p + ((Elf64_Ehdr*)p)->e_phoff))
# define SECT_HDRS64(p) ((Elf64_Shdr*)((void*)p + ((Elf64_Ehdr*)p)->e_shoff))

#endif
