/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:09:16 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/26 00:14:27 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	check_sections(t_macho64 *macho,
					unsigned char *content_file, unsigned int *sect_num)
{
	unsigned int	j;
	t_macho64_seg	segment;
	t_macho64_sect	section;

	segment = *(t_macho64_seg *)(content_file);
	j = -1;
	while (++j < segment.nsects)
	{
		section = *(t_macho64_sect *)(content_file + sizeof(segment)
				+ sizeof(section) * j);
		if (!ft_strcmp(section.sectname, "__text"))
			macho->text_sect = *sect_num + 1;
		else if (!ft_strcmp(section.sectname, "__data"))
			macho->data_sect = *sect_num + 1;
		else if (!ft_strcmp(section.sectname, "__bss"))
			macho->bss_sect = *sect_num + 1;
		*sect_num += 1;
	}
}

static t_macho64	fill_macho(unsigned char *content_file)
{
	t_macho64		macho;
	unsigned int	i;
	t_macho64_seg	loadc;
	unsigned int	sect_num;

	macho.hdr = *(t_macho64_hdr *)content_file;
	macho.text_sect = -1;
	macho.data_sect = -1;
	macho.bss_sect = -1;
	i = -1;
	sect_num = 0;
	content_file += sizeof(macho.hdr);
	while (++i < macho.hdr.ncmds)
	{
		loadc = *(t_macho64_seg *)(content_file);
		if (loadc.cmd == LC_SEGMENT_64)
			check_sections(&macho, content_file, &sect_num);
		content_file += loadc.cmdsize;
	}
	return (macho);
}

static int	find_macho_symboltable(t_macho64 macho,
							unsigned char *content_file)
{
	unsigned int	i;
	unsigned long	offset;
	t_macho64_loadc	*loadc;
	t_sort			*sort;
	int				sym_check;

	i = -1;
	offset = 0;
	sym_check = 0;
	while (++i < macho.hdr.ncmds)
	{
		loadc = (t_macho64_loadc *)(content_file
				+ sizeof(t_macho64_hdr) + offset);
		if (loadc->cmd == LC_SYMTAB)
		{
			sort = prepare_macho64_sort(
					*(t_macho64_symtab *)loadc, content_file);
			print_macho64_table(macho, sort, *(t_macho64_symtab *)loadc);
			sym_check += 1;
			free(sort);
		}
		offset += loadc->cmdsize;
	}
	return (sym_check);
}

void	macho64(unsigned char *content_file)
{
	t_macho64	macho;
	int			sym_check;

	macho = fill_macho(content_file);
	sym_check = find_macho_symboltable(macho, content_file);
	if (!sym_check)
		nm_error(ERROR_NOSYMB);
}
