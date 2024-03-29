/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_macho32_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:55:56 by jagarcia          #+#    #+#             */
/*   Updated: 2021/08/12 01:55:58 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	print_macho_symbol(t_sort symbol, t_macho32 macho, char *filename)
{
	char	type;

	if (get_flags("-print-file-name"))
		ft_printf("%s: ", filename);
	type = select_macho32_nmtype(*(t_macho32_sym *)symbol.sym, macho);
	if (type == 'U')
		ft_printf("%10c %s\n", type, symbol.name);
	else if (type)
	{
		if (get_flags("-print-size"))
			ft_printf("%08lx %08lx %c %s\n", symbol.value, 0, type, symbol.name);
		else
			ft_printf("%08lx %c %s\n", symbol.value, type, symbol.name);
	}
}

void	print_macho32_table(t_macho32 macho, t_sort *sort,
				t_macho32_symtab symtab, char *filename)
{
	unsigned int		i;

	i = -1;
	while (++i < symtab.nsyms)
	{
		if (get_flags("-reverse-sort"))
			print_macho_symbol(sort[symtab.nsyms - i - 1], macho, filename);
		else
			print_macho_symbol(sort[i], macho, filename);
	}
}
