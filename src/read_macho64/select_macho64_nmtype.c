/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_macho64_nmtype.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 03:43:39 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/25 23:28:01 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	select_macho64_nmtype2(t_macho64_sym symbol, t_macho64 macho)
{
	int	debug;

	debug = symbol.type & N_STAB;
	if (symbol.sect == macho.bss_sect)
	{
		if (symbol.type & N_EXT)
			return ('B');
		return ('b');
	}
	if (debug)
		return ('-');
	if (symbol.type == N_INDR)
		return ('I');
	return ('S');
}

char	select_macho64_nmtype(t_macho64_sym symbol, t_macho64 macho)
{
	int	type;
	int	debug;

	if (symbol.type & 0xe0)
		return ('\0');
	type = symbol.type & N_TYPE;
	debug = symbol.type & N_STAB;
	if (type == N_UNDF)
		return ('U');
	if (type == N_ABS)
		return ('A');
	if (symbol.sect == macho.text_sect)
	{
		if (symbol.type & N_EXT)
			return ('T');
		return ('t');
	}
	if (symbol.sect == macho.data_sect)
	{
		if (symbol.type & N_EXT)
			return ('D');
		return ('d');
	}
	return (select_macho64_nmtype2(symbol, macho));
}
