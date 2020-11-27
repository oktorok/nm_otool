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

char	select_pe32_nmtype(t_pe32_symbol symbol, t_pe32 pe32)
{
	short	sect;

	sect = symbol.sect;
	if (sect == IMAGE_SYM_UNDEFINED)
		return ('U');
	if (sect == IMAGE_SYM_ABSOLUTE)
		return ('A');
	if (sect == (short)pe32.text_sect)
		return (symbol.storageclass == IMAGE_SYM_CLASS_EXTERNAL ? 'T' : 't');
	if (sect == (short)pe32.rodata_sect)
		return (symbol.storageclass == IMAGE_SYM_CLASS_EXTERNAL ? 'R' : 'r');
	if (sect == (short)pe32.data_sect)
		return (symbol.storageclass == IMAGE_SYM_CLASS_EXTERNAL ? 'D' : 'd');
	if (sect == (short)pe32.bss_sect)
		return (symbol.storageclass == IMAGE_SYM_CLASS_EXTERNAL ? 'B' : 'b');
	if (sect == IMAGE_SYM_DEBUG)
		return ('-');
	return ('S');
}
