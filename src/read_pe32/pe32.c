/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pe32.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 15:38:23 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/26 00:16:36 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	fill_sections(t_pe32 *pe32, unsigned char *content_file)
{
	unsigned short	i;
	unsigned long	offset;
	char			*name;

	offset = pe32->doshdr.lfanew + 4 + sizeof(t_pe32_coffhdr)
		+ pe32->coffhdr.size_opthdr;
	pe32->sections = (t_pe32_section *)(content_file + offset);
	i = 0;
	pe32->data_sect = -1;
	pe32->text_sect = -1;
	pe32->bss_sect = -1;
	while (i < pe32->coffhdr.nsect)
	{
		name = (char *)pe32->sections[i].name;
		if (!ft_strcmp(".text", name))
			pe32->text_sect = i + 1;
		else if (!ft_strcmp(".data", name))
			pe32->data_sect = i + 1;
		else if (!ft_strcmp(".bss", name))
			pe32->bss_sect = i + 1;
		else if (!ft_strcmp(".rdata", name))
			pe32->rodata_sect = i + 1;
		i++;
	}
}

static t_pe32	fill_pe32(unsigned char *content_file)
{
	t_pe32	pe32;

	pe32.doshdr = *(t_pe32_doshdr *)(content_file);
	pe32.coffhdr = *(t_pe32_coffhdr *)(content_file + pe32.doshdr.lfanew + 4);
	pe32.opthdr = *(t_pe32_opthdr *)(content_file + pe32.doshdr.lfanew
			+ 4 + sizeof(pe32.coffhdr));
	if (!pe32.coffhdr.nsymbols)
	{
		ft_printf("No symbols\n");
		pe32.symboltable = NULL;
		return (pe32);
	}
	pe32.symboltable = content_file + pe32.coffhdr.offsymtable;
	pe32.strtable = content_file + pe32.coffhdr.offsymtable
		+ pe32.coffhdr.nsymbols * 18;
	fill_sections(&pe32, content_file);
	return (pe32);
}

int	pe32(unsigned char *content_file, char *filename)
{
	t_pe32	pe32;
	t_sort	*sort;

	pe32 = fill_pe32(content_file);
	if (!pe32.symboltable)
		return (1);
	sort = prepare_pe32_sort(pe32);
	print_pe32_table(pe32, sort, filename);
	free(sort);
	return (1);
}
