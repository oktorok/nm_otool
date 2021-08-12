/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_gnu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:21:15 by jagarcia          #+#    #+#             */
/*   Updated: 2021/08/12 01:49:19 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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

static char	*print_filename_gnu(unsigned char *content_file,
								unsigned char *strtable, char *filename)
{
	unsigned char	*name;
	char			*name_alloc;
	int				i;

	if (*content_file == '/')
		name = strtable + ft_atoi((char *)content_file + 1);
	else
		name = content_file;
	i = 0;
	while (name[i] != '/')
		i++;
	if (!get_flags("-print-file-name"))
	{
		ft_putendl("");
		write(1, name, i);
		ft_putendl(":");
		return (filename);
	}
	name_alloc = ft_memalloc(i + ft_strlen(filename) + 1);
	ft_asprintf(&name_alloc, "%s:%s", filename, ft_memcpy(name_alloc, name, i));
	return (name_alloc);
}

void	arch_gnu(unsigned char *content_file, char *filename)
{
	t_arch			arch;
	unsigned int	offset;
	unsigned int	j;
	char			*filename2;

	arch = fill_arch(content_file);
	j = 0;
	while (j < arch.objnum)
	{
		offset = big_to_lit(arch.object.offset[j]);
		if (!j || offset != big_to_lit(arch.object.offset[j - 1]))
		{
			filename2 = print_filename_gnu(content_file + offset, arch.strtable,
					filename);
			choose_format(content_file + offset + 60, filename2);
			if (get_flags("-print-file-name"))
				free(filename2);
		}
		j++;
	}
}
