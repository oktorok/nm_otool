/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:45:32 by jagarcia          #+#    #+#             */
/*   Updated: 2021/08/12 02:29:10 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "ft_otool.h"

static char	g_allflags[][20] = {"-h", ""};
static int	g_flags = 0;

char	**set_flags(char **argv, int *argn)
{
	int	i;

	while (*(++argv))
	{
		i = 0;
		while (g_allflags[i][0] && ft_strcmp(g_allflags[i], *argv))
			i++;
		if (!g_allflags[i][0])
			return (argv);
		g_flags |= (1 << i);
		(*argn)--;
	}
	return (argv);
}

int	get_flags(char *f)
{
	int	i;

	i = 0;
	while (g_allflags[i][0])
	{
		if (!ft_strcmp(f, g_allflags[i]) && g_flags & (1 << i))
			return (1);
		i++;
	}
	return (0);
}
