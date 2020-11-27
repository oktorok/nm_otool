/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:40:11 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/27 02:55:15 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	check_magic(unsigned char *content_file)
{
	if (*(unsigned int *)content_file == ELF_MAGIC)
		return (ELF);
	else if (*(unsigned long *)content_file == ARCH_MAGIC)
		return (ARCH);
	else if (*(unsigned int *)content_file == MACHO64_MAGIC)
		return (MACHO64);
	else if (*(unsigned int *)content_file == MACHO32_MAGIC)
		return (MACHO32);
	else if (*(unsigned short *)content_file == PE_MAGIC)
		return (PE);
	return (-1);
}

static int	choose_arch_format(unsigned char *content_file, char *filename)
{
	if (*(content_file + sizeof(ARCH_MAGIC)) == '/')
		arch_gnu(content_file);
	else if (*(content_file + sizeof(ARCH_MAGIC)) == '#')
		arch_bsd(content_file, filename);
	else
		return (0);
	return (1);
}

static int	choose_elf_format(unsigned char *content_file)
{
	if (content_file[4] == 2)
		elf64(content_file);
	else if (content_file[4] == 1)
		elf32(content_file);
	else
		return (0);
	return (1);
}

int			choose_format(unsigned char *content_file, char *filename)
{
	int	format;
	int	ret;

	format = check_magic(content_file);
	ret = 1;
	if (format == ELF)
		ret = choose_elf_format(content_file);
	else if (format == ARCH)
		ret = choose_arch_format(content_file, filename);
	else if (format == MACHO64)
		macho64(content_file);
	else if (format == MACHO32)
		macho32(content_file);
	else if (format == PE)
		pe32(content_file);
	else
		return (0);
	return (ret);
}
