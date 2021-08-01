/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:05:12 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/26 00:15:17 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <elf.h>

static void	fill_elf_specialsegments(t_elf32 *elf,
									unsigned char *content_file)
{
	char			*shstrtable;
	char			*name;
	unsigned short	i;

	shstrtable = (char *)content_file + elf->shdr[elf->ehdr.shstrndx].offset;
	i = 0;
	while (i < elf->ehdr.shnum)
	{
		name = shstrtable + elf->shdr[i].name;
		if (!ft_strcmp(name, ".data"))
			elf->data = find_elf32_segment(*elf, i);
		else if (!ft_strcmp(name, ".bss"))
			elf->bss = find_elf32_segment(*elf, i);
		else if (!ft_strcmp(name, ".text"))
			elf->text = find_elf32_segment(*elf, i);
		else if (ft_strstr(name, ".text.__x86.get_pc_thunk.ax"))
			elf->text32a = find_elf32_segment(*elf, i);
		else if (ft_strstr(name, ".text.__x86.get_pc_thunk.bx"))
			elf->text32b = find_elf32_segment(*elf, i);
		else if (!ft_strcmp(name, ".rodata"))
			elf->rodata = find_elf32_segment(*elf, i);
		i++;
	}
}

static t_elf32	fill_elf(unsigned char *content_file)
{
	t_elf32	elf;

	elf.ehdr = *(t_elf32_eheader *)content_file;
	if (!elf.ehdr.phoff)
		elf.phdr = NULL;
	else
		elf.phdr = (t_elf32_pheader *)(content_file + elf.ehdr.phoff);
	elf.shdr = (t_elf32_sheader *)(content_file + elf.ehdr.shoff);
	return (elf);
}

static void	find_elf_symboltable(t_elf32 elf,
							unsigned char *content_file)
{
	unsigned long	i;
	t_sort			*sort;
	unsigned long	symlen;

	i = 0;
	while (i < elf.ehdr.shnum)
	{
		if (elf.shdr[i].type == SHT_SYMTAB)
		{
			symlen = elf.shdr[i].size / elf.shdr[i].entsize;
			sort = prepare_elf32_sort(elf, content_file, i, symlen);
			print_elf32_table(elf, sort, symlen);
			free(sort);
		}
		i++;
	}
}

void	elf32(unsigned char *content_file)
{
	t_elf32	elf;

	elf = fill_elf(content_file);
	fill_elf_specialsegments(&elf, content_file);
	find_elf_symboltable(elf, content_file);
}
