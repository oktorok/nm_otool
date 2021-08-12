/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:09:04 by jagarcia          #+#    #+#             */
/*   Updated: 2021/08/12 02:34:35 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	print_elf_symbol(t_sort sort, t_elf64 elf, char *filename)
{
	t_elf64_symb	sym;
	int				type;
	char			t;

	sym = *(t_elf64_symb *)sort.sym;
	type = sym.info & 0xf;
	if (type != STT_SECTION && type != STT_FILE && *sort.name)
	{
		if (get_flags("-print-file-name"))
			ft_printf("%s: ", filename);
		t = select_elf64_nmtype(sort, elf);
		if (sym.shndx != SHN_UNDEF)
		{
			ft_printf("%016lx ", sort.value);
			if (get_flags("-print-size") && sym.size)
				ft_printf("%016lx ", sym.size);
			ft_printf("%c %s\n", t, sort.name);
		}
		else
			ft_printf("%18c %s\n", t, sort.name);
	}
}

void	print_elf64_table(t_elf64 elf, t_sort *sorted,
			  unsigned long symlen, char *filename)
{
	unsigned long	i;

	i = 0;
	while (i < symlen)
	{
		if (get_flags("-reverse-sort"))
			print_elf_symbol(sorted[symlen - i - 1], elf, filename);
		else
			print_elf_symbol(sorted[i], elf, filename);
		i++;
	}
}
