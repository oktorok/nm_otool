/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matcho.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 17:36:08 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/25 18:21:00 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MACHO_H
# define FT_MACHO_H
# define LC_SEGMENT_64	0x19
# define LC_SEGMENT	0x1
# define LC_SYMTAB	0x2
# define N_TYPE	0x0e
# define N_STAB	0xe0
# define N_UNDF	0x0
# define N_ABS	0x2
# define N_INDR	0xa
# define N_EXT	0x01

typedef struct s_macho64_hdr {
	unsigned int		magic;
	unsigned int		cputype;
	unsigned int		cpusubtype;
	unsigned int		filetype;
	unsigned int		ncmds;
	unsigned int		sizeofcmds;
	unsigned int		flags;
	unsigned int		reserved;
}						t_macho64_hdr;
typedef struct s_macho64_loadc {
	unsigned int		cmd;
	unsigned int		cmdsize;
}						t_macho64_loadc;
typedef struct s_macho64_symtab {
	unsigned int		cmd;
	unsigned int		cmdsize;
	unsigned int		symoff;
	unsigned int		nsyms;
	unsigned int		stroff;
	unsigned int		strsize;
}						t_macho64_symtab;
typedef struct s_macho64_sym {
	unsigned int		strx;
	unsigned char		type;
	unsigned char		sect;
	unsigned short		desc;
	unsigned long		value;
}						t_macho64_sym;
typedef struct s_macho64_seg {
	unsigned int		cmd;
	unsigned int		cmdsize;
	char				segname[16];
	unsigned long		vmaddr;
	unsigned long		vmsize;
	unsigned long		fileoff;
	unsigned long		filesize;
	int					maxprot;
	int					initprot;
	unsigned int		nsects;
	unsigned int		flags;
}						t_macho64_seg;
typedef struct s_macho64_sect {
	char				sectname[16];
	char				segname[16];
	unsigned long		addr;
	unsigned long		size;
	unsigned int		offset;
	unsigned int		align;
	unsigned int		reloff;
	unsigned int		nreloc;
	unsigned int		flags;
	unsigned int		reserved1;
	unsigned int		reserved2;
}						t_macho64_sect;
typedef struct s_macho64 {
	t_macho64_hdr		hdr;
	unsigned int		text_sect;
	unsigned int		bss_sect;
	unsigned int		data_sect;
}						t_macho64;
typedef struct s_macho32_hdr {
	unsigned int		magic;
	unsigned int		cputype;
	unsigned int		cpusubtype;
	unsigned int		filetype;
	unsigned int		ncmds;
	unsigned int		sizeofcmds;
	unsigned int		flags;
}						t_macho32_hdr;
typedef struct s_macho32_loadc {
	unsigned int		cmd;
	unsigned int		cmdsize;
}						t_macho32_loadc;
typedef struct s_macho32_symtab {
	unsigned int		cmd;
	unsigned int		cmdsize;
	unsigned int		symoff;
	unsigned int		nsyms;
	unsigned int		stroff;
	unsigned int		strsize;
}						t_macho32_symtab;
typedef struct s_macho32_sym {
	unsigned int		strx;
	unsigned char		type;
	unsigned char		sect;
	unsigned short		desc;
	unsigned int		value;
}						t_macho32_sym;
typedef struct s_macho32_seg {
	unsigned int		cmd;
	unsigned int		cmdsize;
	char				segname[16];
	unsigned int		vmaddr;
	unsigned int		vmsize;
	unsigned int		fileoff;
	unsigned int		filesize;
	int					maxprot;
	int					initprot;
	unsigned int		nsects;
	unsigned int		flags;
}						t_macho32_seg;
typedef struct s_macho32_sect {
	char				sectname[16];
	char				segname[16];
	unsigned int		addr;
	unsigned int		size;
	unsigned int		offset;
	unsigned int		align;
	unsigned int		reloff;
	unsigned int		nreloc;
	unsigned int		flags;
	unsigned int		reserved1;
	unsigned int		reserved2;
}						t_macho32_sect;
typedef struct s_macho32 {
	t_macho32_hdr		hdr;
	unsigned int		text_sect;
	unsigned int		bss_sect;
	unsigned int		data_sect;
}						t_macho32;
#endif
