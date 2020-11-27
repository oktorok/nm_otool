/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:21:25 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/25 23:52:09 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ELF_H
# define FT_ELF_H

# define STT_SECTION 3
# define STT_FILE    4
# define SHT_PROGBITS	1
# define SHT_SYMTAB	2
# define SHT_NOBITS	8
# define SHN_UNDEF	0
# define SHN_ABS		0xfff1
# define SHN_COMMON	0xfff2
# define STB_GLOBAL 1
# define STB_WEAK   2
# define PF_R 0x4

typedef struct		s_elf32_eheader {
	unsigned char	ident[16];
	unsigned short	type;
	unsigned short	machine;
	unsigned int	version;
	unsigned int	entry;
	unsigned int	phoff;
	unsigned int	shoff;
	unsigned int	flags;
	unsigned short	ehsize;
	unsigned short	phentsize;
	unsigned short	phnum;
	unsigned short	shentsize;
	unsigned short	shnum;
	unsigned short	shstrndx;
}					t_elf32_eheader;

typedef struct		s_elf32_pheader {
	unsigned int	type;
	unsigned int	offset;
	unsigned int	vaddr;
	unsigned int	paddr;
	unsigned int	filesz;
	unsigned int	memsz;
	unsigned int	flags;
	unsigned int	align;
}					t_elf32_pheader;

typedef struct		s_elf32_sheader {
	unsigned int	name;
	unsigned int	type;
	unsigned int	flags;
	unsigned int	addr;
	unsigned int	offset;
	unsigned int	size;
	unsigned int	link;
	unsigned int	info;
	unsigned int	addralign;
	unsigned int	entsize;
}					t_elf32_sheader;

typedef struct		s_elf32_symb {
	unsigned int	name;
	unsigned int	value;
	unsigned int	size;
	unsigned char	info;
	unsigned char	other;
	unsigned short	shndx;
}					t_elf32_symb;

typedef struct		s_elf32 {
	t_elf32_eheader	ehdr;
	t_elf32_pheader	*phdr;
	t_elf32_sheader	*shdr;
	t_elf32_symb	**symbtable;
	unsigned char	*shstrtable;
	unsigned char	*strtable;
	unsigned short	text;
	unsigned short	text32a;
	unsigned short	text32b;
	unsigned short	data;
	unsigned short	rodata;
	unsigned short	bss;
}					t_elf32;

typedef struct		s_elf64_eheader {
	unsigned char	ident[16];
	unsigned short	type;
	unsigned short	machine;
	unsigned int	version;
	unsigned long	entry;
	unsigned long	phoff;
	unsigned long	shoff;
	unsigned int	flags;
	unsigned short	ehsize;
	unsigned short	phentsize;
	unsigned short	phnum;
	unsigned short	shentsize;
	unsigned short	shnum;
	unsigned short	shstrndx;
}					t_elf64_eheader;

typedef struct		s_elf64_pheader {
	unsigned int	type;
	unsigned int	flags;
	unsigned long	offset;
	unsigned long	vaddr;
	unsigned long	paddr;
	unsigned long	filesz;
	unsigned long	memsz;
	unsigned long	align;
}					t_elf64_pheader;

typedef struct		s_elf64_sheader {
	unsigned int	name;
	unsigned int	type;
	unsigned long	flags;
	unsigned long	addr;
	unsigned long	offset;
	unsigned long	size;
	unsigned int	link;
	unsigned int	info;
	unsigned long	addralign;
	unsigned long	entsize;
}					t_elf64_sheader;

typedef struct		s_elf64_symb {
	unsigned int	name;
	unsigned char	info;
	unsigned char	other;
	unsigned short	shndx;
	unsigned long	value;
	unsigned long	size;
}					t_elf64_symb;

typedef struct		s_elf64 {
	t_elf64_eheader	ehdr;
	t_elf64_pheader	*phdr;
	t_elf64_sheader	*shdr;
	t_elf64_symb	**symbtable;
	unsigned char	*shstrtable;
	unsigned char	*strtable;
	unsigned short	text;
	unsigned short	data;
	unsigned short	rodata;
	unsigned short	bss;
}					t_elf64;
#endif
