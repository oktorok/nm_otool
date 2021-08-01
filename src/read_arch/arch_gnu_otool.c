/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_gnu_otool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:21:15 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/27 01:03:37 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static unsigned int	big_to_lit(int a)
{
	int	b;

	b = ((a & 0xFF000000) >> 24)
		| ((a & 0x00FF0000) >> 8)
		| ((a & 0x0000FF00) << 8)
		| ((a & 0x000000FF) << 24);
	return (b);
}

static t_arch	fill_arch(unsigned char *content_file)
{
	t_arch	arch;
	int		arch_size;

	content_file += sizeof(ARCH_MAGIC);
	arch_size = ft_atoi((char *)content_file + 48);
	content_file += 60;
	arch.objnum = big_to_lit(*(int *)content_file);
	arch.object.offset = (unsigned int *)(content_file + 4);
	content_file += arch_size;
	arch.strtable = content_file;
	if (arch.strtable[0] == '/' && arch.strtable[1] == '/')
		arch.strtable += 60;
	else
		arch.strtable = NULL;
	return (arch);
}

static void	print_filename_gnu(unsigned char *content_file,
								unsigned char *strtable)
{
	unsigned char	*name;

	ft_putendl("");
	if (*content_file == '/')
		name = strtable + ft_atoi((char *)content_file + 1);
	else
		name = content_file;
	while (*name != '/')
		write(1, name++, 1);
	ft_putendl(":");
}

void	arch_gnu(unsigned char *content_file)
{
	t_arch			arch;
	unsigned int	offset;
	unsigned int	j;

	arch = fill_arch(content_file);
	j = 0;
	while (j < arch.objnum)
	{
		offset = big_to_lit(arch.object.offset[j]);
		if (!j || offset != big_to_lit(arch.object.offset[j - 1]))
		{
			print_filename_gnu(content_file + offset, arch.strtable);
			choose_format(content_file + offset + 60, NULL);
		}
		j++;
	}
}
