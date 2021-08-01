/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:34:59 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/27 02:53:26 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	print_section(unsigned char *section, unsigned long size, char bits,
			unsigned long offset)
{
	unsigned long	byte;

	byte = 0;
	while (byte < size)
	{
		if (!(byte % 16))
		{
			if (bits == X64)
				ft_printf("\n%016lx        ", byte + offset);
			else if (bits == X32)
				ft_printf("\n%08lx        ", byte + offset);
			else
				nm_error(ERROR_FORMAT);
		}
		ft_printf("%02hhx ", *(section + byte));
		byte += 1;
	}
}
