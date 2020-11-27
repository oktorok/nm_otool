/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_macho64_sort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 03:09:21 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/23 21:40:21 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_sort	*prepare_macho64_sort(t_macho64_symtab symtab,
							unsigned char *content_file)
{
	t_sort			*sort;
	t_macho64_sym	*symbol;
	unsigned int	i;

	if (!(sort = ft_memalloc(sizeof(t_sort) * symtab.nsyms)))
		nm_error(ERROR_ALLOC);
	i = 0;
	while (i < symtab.nsyms)
	{
		symbol = (t_macho64_sym *)(content_file + symtab.symoff +
								sizeof(t_macho64_sym) * i);
		sort[i] = (t_sort){
			symbol,
			content_file + symtab.stroff + symbol->strx,
			symbol->value,
			symbol->sect,
			i++
		};
	}
	sort = order_symb_alpha(sort, symtab.nsyms, SLASH);
	return (sort);
}
