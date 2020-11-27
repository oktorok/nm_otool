/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_elf32_segment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:52:11 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/25 04:10:34 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

unsigned short		find_elf32_segment(t_elf32 elf, unsigned short shndx)
{
	unsigned short	i;
	t_elf32_sheader	sh;

	if (shndx >= elf.ehdr.shnum)
		return (-1);
	if (!elf.ehdr.phnum)
		return (shndx);
	sh = elf.shdr[shndx];
	i = -1;
	while (++i < elf.ehdr.phnum)
	{
		if (elf.phdr[i].offset <= sh.offset && elf.phdr[i].offset +
			elf.phdr[i].memsz >= sh.offset)
			return (i);
	}
	return (-1);
}
