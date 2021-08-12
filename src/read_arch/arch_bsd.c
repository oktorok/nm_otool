/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_bsd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:24:03 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/24 19:29:18 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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

static void	print_object(t_arch_ranlib ranlib, unsigned char *content_file,
			char *filename)
{
	unsigned long	offset;

	offset = ranlib.offset;
	if (!get_flags("-print-file-name"))
		ft_printf("\n%s(%s):\n", filename, content_file + offset + 60);
	else
		ft_asprintf(&filename, "%s:%s", filename, content_file + offset + 60);
	offset += ft_atoi((char *)content_file + offset + 3);
	if (!choose_format(content_file + offset + 60, filename))
		ft_printf(ERROR_FORMAT);
	if (get_flags("-print-file-name"))
		free(filename);
}

static t_sort	*prepare_archbsd_sort(t_arch arch)
{
	t_sort			*sort;
	unsigned int	i;

	sort = ft_memalloc(sizeof(t_sort) * arch.objnum);
	if (!sort)
		nm_error(ERROR_ALLOC);
	i = -1;
	while (++i < arch.objnum)
	{
		sort[i] = (t_sort){
			NULL,
			NULL,
			arch.object.ranlib[i].offset,
			0,
			i
		};
	}
	sort = order_objects_offset(sort, arch.objnum);
	return (sort);
}

void	arch_bsd(unsigned char *content_file, char *filename)
{
	t_arch			arch;
	unsigned int	i;
	t_sort			*sort;

	arch = fill_arch(content_file);
	i = 0;
	sort = prepare_archbsd_sort(arch);
	while (i < arch.objnum)
	{
		if (!i || arch.object.ranlib[sort[i - 1].i].offset
			!= arch.object.ranlib[sort[i].i].offset)
		{
			print_object(arch.object.ranlib[sort[i].i], content_file, filename);
			i++;
		}
		else
			i++;
	}
	free(sort);
}
