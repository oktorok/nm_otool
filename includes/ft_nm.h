/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:46:13 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/26 19:06:14 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

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

typedef struct s_sort {
	void			*sym;
	unsigned char	*name;
	unsigned long	value;
	unsigned long	segment;
	unsigned long	i;
}					t_sort;
int					main(int argn, char **argv);
t_sort				*order_symb_alpha(t_sort *sort, unsigned long symlen,
						char check_slash);
void				nm_error(char *err);
int					strcmp_onlyalph(const char *s1, const char *s2);
void				swap_value(t_sort *a, t_sort *b);
int					choose_format(unsigned char *content_file, char *filename);
void				elf64(unsigned char *content_file);
void				print_elf64_table(t_elf64 elf, t_sort *sorted,
						unsigned long symlen);
t_sort				*prepare_elf64_sort(t_elf64 elf,
						unsigned char *content_file,
						unsigned long st_pos, unsigned long symlen);
unsigned long		find_elf64_segment(t_elf64 elf, unsigned long shndx);
char				select_elf64_nmtype(t_sort sort, t_elf64 elf);
void				elf32(unsigned char *content_file);
void				print_elf32_table(t_elf32 elf, t_sort *sorted,
						unsigned long symlen);
t_sort				*prepare_elf32_sort(t_elf32 elf,
						unsigned char *content_file,
						unsigned long st_pos, unsigned long symlen);
unsigned short		find_elf32_segment(t_elf32 elf, unsigned short shndx);
char				select_elf32_nmtype(t_sort sort, t_elf32 elf);
void				arch_gnu(unsigned char *content_file);
void				arch_bsd(unsigned char *content_file,
						char *filename);
void				macho32(unsigned char *content_file);
void				print_macho32_table(t_macho32 macho, t_sort *sort,
						t_macho32_symtab symtab);
char				select_macho32_nmtype(t_macho32_sym symbol,
						t_macho32 macho);
t_sort				*prepare_macho32_sort(t_macho32_symtab symtab,
						unsigned char *content_file);
void				macho64(unsigned char *content_file, char *filename);
void				print_macho64_table(t_macho64 macho, t_sort *sort,
						    t_macho64_symtab symtab, char *filename);
char				select_macho64_nmtype(t_macho64_sym symbol,
						      t_macho64 macho);
t_sort				*prepare_macho64_sort(t_macho64_symtab symtab,
						unsigned char *content_file);
void				pe32(unsigned char *content_file);
t_sort				*prepare_pe32_sort(t_pe32 pe32);
void				print_pe32_table(t_pe32 pe32, t_sort *sort);
char				select_pe32_nmtype(t_pe32_symbol symbol, t_pe32 pe32);
int					get_flags(char *f);
char				**set_flags(char **argv, int *argn);
int					strcmp_onlyalph_reverse(const char *s1, const char *s2);
t_sort				*order_objects_offset(t_sort *sort, unsigned long objnum);
int				ft_max_sort(int a, int b);

#endif
