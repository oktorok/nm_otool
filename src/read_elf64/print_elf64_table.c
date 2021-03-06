/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:09:04 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/25 05:04:07 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		print_elf_symbol(t_sort sort, t_elf64 elf)
{
	t_elf64_symb	sym;
	int				type;
	char			t;

	sym = *(t_elf64_symb *)sort.sym;
	type = sym.info & 0xf;
	if (type != STT_SECTION && type != STT_FILE && *sort.name)
	{
		t = select_elf64_nmtype(sort, elf);
		if (sym.shndx != SHN_UNDEF)
			ft_printf("%016lx %c %s\n", sort.value, t, sort.name);
		else
			ft_printf("%18c %s\n", t, sort.name);
	}
}

void			print_elf64_table(t_elf64 elf, t_sort *sorted,
								unsigned long symlen)
{
	unsigned long	i;

	i = 0;
	while (i < symlen)
	{
		print_elf_symbol(sorted[i], elf);
		i++;
	}
}
