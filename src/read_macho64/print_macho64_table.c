/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_macho64_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:55:56 by jagarcia          #+#    #+#             */
/*   Updated: 2021/08/12 01:58:56 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	print_macho_symbol(t_sort symbol, t_macho64 macho, char *filename)
{
	char	type;

	type = select_macho64_nmtype(*(t_macho64_sym *)symbol.sym, macho);
	if (get_flags("-print-file-name"))
		ft_printf("%s: ", filename);
	if (type == 'U')
		ft_printf("%18c %s\n", type, symbol.name);
	else if (type)
		ft_printf("%016lx %c %s\n", symbol.value, type, symbol.name);

}

void	print_macho64_table(t_macho64 macho, t_sort *sort,
			    t_macho64_symtab symtab, char *filename)
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
