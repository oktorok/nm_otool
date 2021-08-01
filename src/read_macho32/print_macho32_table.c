/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_macho32_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:55:56 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/25 18:27:03 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	print_macho_symbol(t_sort symbol, t_macho32 macho)
{
	char	type;

	type = select_macho32_nmtype(*(t_macho32_sym *)symbol.sym, macho);
	if (type == 'U')
		ft_printf("%10c %s\n", type, symbol.name);
	else if (type)
		ft_printf("%08lx %c %s\n", symbol.value, type, symbol.name);
}

void	print_macho32_table(t_macho32 macho, t_sort *sort,
							t_macho32_symtab symtab)
{
	unsigned int		i;

	i = -1;
	while (++i < symtab.nsyms)
		print_macho_symbol(sort[i], macho);
}
