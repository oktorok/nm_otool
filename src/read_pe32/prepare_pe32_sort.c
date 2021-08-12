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

static unsigned int	get_virtualaddress(t_pe32 pe32, unsigned int section)
{
	int		match;

	match = 0;
	if (section == pe32.text_sect)
		match = pe32.text_sect;
	else if (section == pe32.bss_sect)
		match = pe32.bss_sect;
	else if (section == pe32.data_sect)
		match = pe32.data_sect;
	else if (section == pe32.rodata_sect)
		match = pe32.rodata_sect;
	else
		return (0);
	if (pe32.opthdr.imagebase)
		return (pe32.sections[match - 1].virtualaddr + pe32.opthdr.imagebase);
	return (pe32.sections[match - 1].virtualaddr + 0x400000);
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
			symbol->value + get_virtualaddress(pe32, symbol->sect),
			symbol->sect, i
		};
	}
	sort = order_symb_alpha(sort, pe32.coffhdr.nsymbols, SLASH);
	return (sort);
}
