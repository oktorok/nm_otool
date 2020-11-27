/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64_otool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:09:16 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/27 02:19:08 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void			check_sections(unsigned char *content_file, unsigned long offset)
{
	unsigned int	j;
	t_macho64_seg	segment;
	t_macho64_sect	*section;

	segment = *(t_macho64_seg *)(content_file + offset);
	j = -1;
	while (++j < segment.nsects)
	{
		section = (t_macho64_sect *)(content_file + offset + sizeof(segment) +
									sizeof(section) * j);
		if (!ft_strcmp(section->sectname, "__text"))
		{
			ft_printf("Content of (%s, %s):", section->segname, section->sectname);
			print_section(content_file + section->offset, section->size, X64);
		}
	}
}

static t_macho64	find_text_section(t_macho64 macho, unsigned char *content_file)
{
	unsigned int	i;
	t_macho64_seg	loadc;
	unsigned long	offset;
	
	i = -1;
	offset = sizeof(macho.hdr);
	while (++i < macho.hdr.ncmds)
	{
		loadc = *(t_macho64_seg *)(content_file + offset);
		if (loadc.cmd == LC_SEGMENT_64)
			check_sections(content_file, offset);
		offset += loadc.cmdsize;
	}
	return (macho);
}

void				macho64(unsigned char *content_file)
{
	t_macho64	macho;

	macho.hdr = *(t_macho64_hdr *)content_file;
	find_text_section(macho, content_file);
}
