/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_elf64_nmtype.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:10:08 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/25 05:02:39 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	select_elf64_nmtype2(t_sort sort, t_elf64 elf)
{
	unsigned short	shndx;
	unsigned char	bind;

	bind = ((t_elf64_symb *)sort.sym)->info >> 4;
	shndx = ((t_elf64_symb *)sort.sym)->shndx;
	if (shndx && elf.text == sort.segment)
		return ((bind == STB_GLOBAL ? 'T' : 't'));
	if (shndx && elf.phdr[sort.segment].flags == PF_R)
		return ((bind == STB_GLOBAL ? 'R' : 'r'));
	if (shndx == SHN_UNDEF)
		return ('U');
	return ('?');
}

char		select_elf64_nmtype(t_sort sort, t_elf64 elf)
{
	unsigned short	shndx;
	unsigned char	bind;

	bind = ((t_elf64_symb *)sort.sym)->info >> 4;
	shndx = ((t_elf64_symb *)sort.sym)->shndx;
	if (shndx == SHN_ABS)
		return ('A');
	if (shndx == SHN_COMMON)
		return ('C');
	if (shndx && elf.shdr[shndx].type == SHT_NOBITS)
		return ((bind == STB_GLOBAL ? 'B' : 'b'));
	if (bind == STB_WEAK)
	{
		if (shndx == SHN_UNDEF)
			return ('w');
		return ('W');
	}
	if (shndx && elf.data == sort.segment)
		return ((bind == STB_GLOBAL ? 'D' : 'd'));
	return (select_elf64_nmtype2(sort, elf));
}
