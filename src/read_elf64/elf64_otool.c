/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64_otool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:05:12 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/27 02:50:51 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static t_elf64		fill_elf(unsigned char *content_file)
{
	t_elf64	elf;

	elf.ehdr = *(t_elf64_eheader *)content_file;
	elf.phdr = (t_elf64_pheader *)(content_file + elf.ehdr.phoff);
	elf.shdr = (t_elf64_sheader *)(content_file + elf.ehdr.shoff);
	return (elf);
}

static void			find_text_section(t_elf64 *elf,
									unsigned char *content_file)
{
	char			*shstrtable;
	char			*name;
	int				i;

	shstrtable = (char *)content_file + elf->shdr[elf->ehdr.shstrndx].offset;
	i = 0;
	while (i < elf->ehdr.shnum)
	{
		name = shstrtable + elf->shdr[i].name;
		if (!ft_strcmp(name, ".text"))
		{
			ft_printf("Content of %s:", name);
			print_section(content_file + elf->shdr[i].offset,
						elf->shdr[i].size, X64);
		}
		i++;
	}
}

void				elf64(unsigned char *content_file)
{
	t_elf64	elf;

	elf = fill_elf(content_file);
	find_text_section(&elf, content_file);
}
