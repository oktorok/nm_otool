/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:33:10 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/23 19:42:34 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARCH_H
# define FT_ARCH_H
# define BSD_MODE 1
# define GNU_MODE 2

typedef struct s_arch_hdr {
	char			name[16];
	char			date[12];
	char			uid[6];
	char			gid[6];
	char			mode[8];
	char			size[10];
	char			fmag[2];
}					t_arch_hdr;
typedef struct s_arch_ranlib {
	unsigned int	strx;
	unsigned int	offset;
}					t_arch_ranlib;
typedef union u_object {
	unsigned int	*offset;
	t_arch_ranlib	*ranlib;
}					t_object;
typedef struct s_arch {
	unsigned char	*strtable;
	unsigned int	objnum;
	t_object		object;
}					t_arch;
#endif
