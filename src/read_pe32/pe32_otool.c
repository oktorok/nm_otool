/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pe32_otool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 15:38:23 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/27 02:52:24 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void		find_text_section(t_pe32 pe32, unsigned char *content_file)
{
	unsigned short	i;
	unsigned long	offset;
	t_pe32_section	section;

	offset = pe32.doshdr.lfanew + 4 + sizeof(t_pe32_coffhdr) +
		pe32.coffhdr.size_opthdr;
	i = 0;
	while (i < pe32.coffhdr.nsect)
	{
		section = *(t_pe32_section *)(content_file + offset + i *
									sizeof(t_pe32_section));
		if (!ft_strcmp(".text", (char *)section.name))
		{
			ft_printf("Content of %s:", section.name);
			print_section(content_file + section.offdata,
						section.sizedata, X64);
		}
		i++;
	}
}

static t_pe32	fill_pe32(unsigned char *content_file)
{
	t_pe32	pe32;

	pe32.doshdr = *(t_pe32_doshdr *)(content_file);
	pe32.coffhdr = *(t_pe32_coffhdr *)(content_file + pe32.doshdr.lfanew + 4);
	return (pe32);
}

void			pe32(unsigned char *content_file)
{
	t_pe32	pe32;

	pe32 = fill_pe32(content_file);
	find_text_section(pe32, content_file);
}
