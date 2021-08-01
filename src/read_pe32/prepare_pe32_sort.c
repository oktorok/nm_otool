/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_pe32_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 04:01:14 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/23 21:47:32 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static unsigned char	*set_symbol_name(t_pe32_symbol *symbol,
							unsigned char *strtable)
{
	if (symbol->name.offset[0])
		return ((unsigned char *)symbol);
	else
		return (strtable + symbol->name.offset[1]);
}

t_sort	*prepare_pe32_sort(t_pe32 pe32)
{
	t_sort			*sort;
	t_pe32_symbol	*symbol;
	unsigned int	i;

	sort = ft_memalloc(sizeof(t_sort) * pe32.coffhdr.nsymbols);
	if (!sort)
		nm_error(ERROR_ALLOC);
	i = -1;
	while (++i < pe32.coffhdr.nsymbols)
	{
		symbol = (t_pe32_symbol *)(pe32.symboltable + i * 18);
		if (symbol->n_auxsymbol)
		{
			i += symbol->n_auxsymbol + 1;
			continue ;
		}
		sort[i] = (t_sort){
			symbol,
			set_symbol_name(symbol, pe32.strtable),
			symbol->value,
			symbol->sect, i
		};
	}
	sort = order_symb_alpha(sort, pe32.coffhdr.nsymbols, SLASH);
	return (sort);
}
