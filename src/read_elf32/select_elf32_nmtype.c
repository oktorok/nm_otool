/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_elf32_nmtype.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:10:08 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/25 05:00:01 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	select_elf32_nmtype3(t_sort sort)
{
	unsigned short	shndx;

	shndx = ((t_elf32_symb *)sort.sym)->shndx;
	if (shndx == SHN_UNDEF)
		return ('U');
	return ('?');
}

static char	select_elf32_nmtype2(t_sort sort, t_elf32 elf)
{
	unsigned short	shndx;
	unsigned char	bind;

	bind = ((t_elf32_symb *)sort.sym)->info >> 4;
	shndx = ((t_elf32_symb *)sort.sym)->shndx;
	if (shndx && elf.data == sort.segment)
	{
		if (bind == STB_GLOBAL)
			return ('D');
		return ('d');
	}
	if (shndx && (elf.text == sort.segment || elf.text32a == sort.segment
			|| elf.text32b == sort.segment))
	{
		if (bind == STB_GLOBAL)
			return ('T');
		return ('t');
	}
	if (shndx && elf.ehdr.phoff && elf.phdr[sort.segment].flags == PF_R)
	{
		if (bind == STB_GLOBAL)
			return ('R');
		return ('r');
	}
	return (select_elf32_nmtype3(sort));
}

char	select_elf32_nmtype(t_sort sort, t_elf32 elf)
{
	unsigned short	shndx;
	unsigned char	bind;

	bind = ((t_elf32_symb *)sort.sym)->info >> 4;
	shndx = ((t_elf32_symb *)sort.sym)->shndx;
	if (shndx == SHN_ABS)
		return ('A');
	if (shndx == SHN_COMMON)
		return ('C');
	if (shndx && elf.shdr[shndx].type == SHT_NOBITS)
	{
		if (bind == STB_GLOBAL)
			return ('B');
		return ('b');
	}
	if (bind == STB_WEAK)
	{
		if (shndx == SHN_UNDEF)
			return ('w');
		return ('W');
	}
	return (select_elf32_nmtype2(sort, elf));
}
