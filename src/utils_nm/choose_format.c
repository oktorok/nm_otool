/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:40:11 by jagarcia          #+#    #+#             */
/*   Updated: 2021/08/11 21:00:59 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*
**
** ARCH = 0; ELF = 1; MACHO64 = 2; MACHO32 = 3; PE32 = 4;
**
*/

static unsigned long	g_magic[] = {0x0a3e686372613c21, 0x464c457F,
					0xfeedfacf, 0xfeedface, 0x5a4d, 0};

static int	check_magic(unsigned char *content_file)
{
	int	i;

	i = -1;
	while (g_magic[++i])
	{
		if ((*(unsigned long *)content_file & g_magic[i]) == g_magic[i])
			return (i);
	}
	return (-1);
}

static int	choose_arch_format(unsigned char *content_file, char *filename)
{
	if (*(content_file + sizeof(ARCH_MAGIC)) == '/')
		arch_gnu(content_file, filename);
	else if (*(content_file + sizeof(ARCH_MAGIC)) == '#')
		arch_bsd(content_file, filename);
	else
		return (0);
	return (1);
}

static int	choose_elf_format(unsigned char *content_file, char *filename)
{
	if (content_file[4] == 2)
		elf64(content_file, filename);
	else if (content_file[4] == 1)
		elf32(content_file, filename);
	else
		return (0);
	filename = NULL;
	return (1);
}

static	int				(*g_format_func[])(unsigned char *, char *) =
			{choose_arch_format, choose_elf_format, macho64, macho32, pe32};

int	choose_format(unsigned char *content_file, char *filename)
{
	int	format;
	int	ret;

	format = check_magic(content_file);
	ret = 1;
	ret = g_format_func[format](content_file, filename);
	return (ret);
}
