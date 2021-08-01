/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pe.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 04:56:10 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/23 16:25:47 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PE_H
# define FT_PE_H
# define IMAGE_SYM_UNDEFINED 0
# define IMAGE_SYM_ABSOLUTE -1
# define IMAGE_SYM_CLASS_EXTERNAL 2
# define IMAGE_SYM_DEBUG -2

typedef struct s_pe32_doshdr {
	unsigned short	magic;
	unsigned short	cblp;
	unsigned short	cp;
	unsigned short	crlc;
	unsigned short	cparhdr;
	unsigned short	minalloc;
	unsigned short	maxalloc;
	unsigned short	ss;
	unsigned short	sp;
	unsigned short	csum;
	unsigned short	ip;
	unsigned short	cs;
	unsigned short	lfarlc;
	unsigned short	ovno;
	unsigned short	res[4];
	unsigned short	oemid;
	unsigned short	oeminfo;
	unsigned short	res2[10];
	unsigned int	lfanew;
}					t_pe32_doshdr;
typedef struct s_pe32_coffhdr {
	unsigned short	machine;
	unsigned short	nsect;
	unsigned int	timestamp;
	unsigned int	offsymtable;
	unsigned int	nsymbols;
	unsigned short	size_opthdr;
	unsigned short	desc;
}					t_pe32_coffhdr;
typedef struct s_pe32_section{
	unsigned char	name[8];
	unsigned int	virtualsize;
	unsigned int	virtualaddr;
	unsigned int	sizedata;
	unsigned int	offdata;
	unsigned int	offreloc;
	unsigned int	offlinenum;
	unsigned short	relocnum;
	unsigned short	linenumnum;
	unsigned int	description;
}					t_pe32_section;
typedef union u_sname {
	char			name[8];
	int				offset[2];
}					t_name;
typedef struct s_pe32_symbol {
	t_name			name;
	unsigned int	value;
	unsigned short	sect;
	unsigned short	type;
	unsigned char	storageclass;
	unsigned char	n_auxsymbol;
}					t_pe32_symbol;
typedef struct s_pe32 {
	t_pe32_doshdr	doshdr;
	t_pe32_coffhdr	coffhdr;
	unsigned char	*strtable;
	void			*symboltable;
	unsigned int	text_sect;
	unsigned int	bss_sect;
	unsigned int	data_sect;
	unsigned int	rodata_sect;
}					t_pe32;
#endif
