/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_elf32_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:03:51 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/24 21:59:36 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_sort	*prepare_elf32_sort(t_elf32 elf, unsigned char *content_file,
							unsigned long st_pos, unsigned long symlen)
{
	unsigned long	i;
	t_sort			*sort;
	t_elf32_symb	*symtable;
	unsigned char	*strtable;

	sort = ft_memalloc(sizeof(t_sort) * symlen);
	if (!sort)
		nm_error(ERROR_ALLOC);
	i = -1;
	symtable = (t_elf32_symb *)(content_file + elf.shdr[st_pos].offset);
	strtable = content_file + elf.shdr[elf.shdr[st_pos].link].offset;
	while (++i < symlen)
	{
		sort[i] = (t_sort){
			(void *)(symtable + i),
			strtable + symtable[i].name,
			symtable[i].value,
			find_elf32_segment(elf, symtable[i].shndx),
			i
		};
	}
	sort = order_symb_alpha(sort, symlen, NO_SLASH);
	return (sort);
}
