/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pe32_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 04:53:02 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/23 21:01:42 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	print_pe_symbol(t_sort symbol, t_pe32 pe32)
{
	char	type;

	type = select_pe32_nmtype(*(t_pe32_symbol *)symbol.sym, pe32);
	if (type == 'U')
	{
		if (((t_pe32_symbol *)symbol.sym)->name.offset[0])
		{
			ft_printf("%18c ", type);
			write(1, symbol.name, 8);
			ft_putendl("");
		}
		else
			ft_printf("%18c %s\n", type, symbol.name);
	}
	else if (((t_pe32_symbol *)symbol.sym)->name.offset[0])
	{
		ft_printf("%08x %c ", symbol.value, type);
		write(1, symbol.name, 8);
		ft_putendl("");
	}
	else
		ft_printf("%08x %c %s\n", symbol.value, type, symbol.name);
}

void	print_pe32_table(t_pe32 pe32, t_sort *sort)
{
	unsigned int	i;

	i = -1;
	while (++i < pe32.coffhdr.nsymbols)
		print_pe_symbol(sort[i], pe32);
}
