/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:11:14 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/27 02:26:33 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include "libft.h"
# include "libftprintf.h"
# include "ft_elf.h"
# include "ft_arch.h"
# include "ft_macho.h"
# include "ft_pe.h"
# define ARCH_MAGIC 0x0a3e686372613c21
# define ARCH 0
# define ELF_MAGIC 0x464c457F
# define ELF 1
# define MACHO64_MAGIC 0xfeedfacf
# define MACHO64 2
# define MACHO32_MAGIC 0xfeedface
# define MACHO32 4
# define PE_MAGIC 0x5a4d
# define PE 3
# define SLASH 1
# define NO_SLASH 0
# define ERROR_ALLOC "Error Allocating Memory"
# define ERROR_FREE "Error Freeing Memory"
# define ERROR_OPEN "Error Opening File"
# define ERROR_READ "Error Reading File"
# define ERROR_FORMAT "Error Format not Recogniced"
# define ERROR_NOSYMB "No symbols"
# define X64	0
# define X32	1

int					main(int argn, char **argv);
void				elf64(unsigned char *content_file);
void				elf32(unsigned char *content_file);
void				macho64(unsigned char *content_file);
void				macho32(unsigned char *content_file);
void				pe32(unsigned char *content_file);
void				nm_error(char *err);
int					choose_format(unsigned char *content_file, char *filename);
void				print_section(unsigned char *section, unsigned long size,
						char bits, unsigned long offset);
void				arch_gnu(unsigned char *content_file);
void				arch_bsd(unsigned char *content_file,
						char *filename);
#endif
