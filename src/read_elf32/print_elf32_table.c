/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:09:04 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/25 04:30:04 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	print_elf_symbol(t_sort sort, t_elf32 elf)
{
	t_elf32_symb	sym;
	unsigned char	type;
	char			t;

	sym = *(t_elf32_symb *)sort.sym;
	type = sym.info & 0xf;
	if (type != STT_SECTION && type != STT_FILE && *sort.name)
	{
		t = select_elf32_nmtype(sort, elf);
		if (sym.shndx != SHN_UNDEF)
			ft_printf("%08lx %c %s\n", sort.value, t, sort.name);
		else
			ft_printf("%10c %s\n", t, sort.name);
	}
}

void	print_elf32_table(t_elf32 elf, t_sort *sorted,
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
