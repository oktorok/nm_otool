/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_bsd_otool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:24:03 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/27 01:03:49 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static t_arch	fill_arch(unsigned char *content_file)
{
	t_arch	arch;
	int		t;

	content_file += sizeof(ARCH_MAGIC);
	t = ft_atoi((char *)content_file + 3);
	content_file += 60 + t;
	arch.objnum = *(int *)(content_file) / sizeof(t_arch_ranlib);
	arch.object.ranlib = (t_arch_ranlib *)(content_file + 4);
	content_file += arch.objnum * sizeof(t_arch_ranlib);
	arch.strtable = content_file + 8;
	return (arch);
}

static void	print_object(t_arch arch, unsigned char *content_file,
								char *filename, int i)
{
	unsigned long	offset;

	offset = arch.object.ranlib[i].offset;
	ft_printf("\n%s(%s):\n", filename, content_file + offset + 60);
	offset += ft_atoi((char *)content_file + offset + 3);
	if (!choose_format(content_file + offset + 60, NULL))
		ft_printf(ERROR_FORMAT);
}

void	arch_bsd(unsigned char *content_file, char *filename)
{
	t_arch			arch;
	unsigned int	i;

	arch = fill_arch(content_file);
	i = 0;
	while (i < arch.objnum)
	{
		if (!i || arch.object.ranlib[i - 1].offset
			!= arch.object.ranlib[i].offset)
			print_object(arch, content_file, filename, i++);
		else
			i++;
	}
}
