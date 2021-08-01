/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_pe32_nmtype.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 06:01:15 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/25 23:29:06 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	select_pe32_nmtype2(t_pe32_symbol symbol, t_pe32 pe32)
{
	short	sect;

	sect = symbol.sect;
	if (sect == (short)pe32.data_sect)
	{
		if (symbol.storageclass == IMAGE_SYM_CLASS_EXTERNAL)
			return ('D');
		return ('d');
	}
	if (sect == (short)pe32.bss_sect)
	{
		if (symbol.storageclass == IMAGE_SYM_CLASS_EXTERNAL)
			return ('B');
		return ('b');
	}	
	if (sect == IMAGE_SYM_DEBUG)
		return ('-');
	return ('S');
}

char	select_pe32_nmtype(t_pe32_symbol symbol, t_pe32 pe32)
{
	short	sect;

	sect = symbol.sect;
	if (sect == IMAGE_SYM_UNDEFINED)
		return ('U');
	if (sect == IMAGE_SYM_ABSOLUTE)
		return ('A');
	if (sect == (short)pe32.text_sect)
	{
		if (symbol.storageclass == IMAGE_SYM_CLASS_EXTERNAL)
			return ('T');
		return ('t');
	}
	if (sect == (short)pe32.rodata_sect)
	{
		if (symbol.storageclass == IMAGE_SYM_CLASS_EXTERNAL)
			return ('R');
		return ('r');
	}
	return (select_pe32_nmtype2(symbol, pe32));
}
