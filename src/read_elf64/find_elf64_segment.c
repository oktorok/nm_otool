/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_elf64_segment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:52:11 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/23 17:11:24 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

unsigned long		find_elf64_segment(t_elf64 elf, unsigned long shndx)
{
	unsigned short	i;
	t_elf64_sheader	sh;

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
