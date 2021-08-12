/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pe32_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 04:53:02 by jagarcia          #+#    #+#             */
/*   Updated: 2021/08/12 03:10:49 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	print_pe_symbol(t_sort symbol, t_pe32 pe32, char *filename)
{
	char	type;

	type = select_pe32_nmtype(*(t_pe32_symbol *)symbol.sym, pe32);
	if (get_flags("-print-file-name"))
		ft_printf("%s: ", filename);
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

void	print_pe32_table(t_pe32 pe32, t_sort *sort, char *filename)
{
	unsigned int	i;

	i = -1;
	while (++i < pe32.coffhdr.nsymbols)
	{
		if (get_flags("-reverse-sort"))
			print_pe_symbol(sort[pe32.coffhdr.nsymbols - i - 1], pe32, filename);
		else
			print_pe_symbol(sort[i], pe32, filename);
	}
}
