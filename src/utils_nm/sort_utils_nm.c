/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:07:25 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/23 21:03:19 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	swap_value(t_sort *a, t_sort *b)
{
	t_sort	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_max_sort(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (0);
}

int	strcmp_onlyalph(const char *s1, const char *s2)
{
	int				j;
	int				i;

	j = 0;
	i = 0;
	while (s1[j] && s2[i])
	{
		while (!ft_isalpha(s1[j]) && !ft_isdigit(s1[j]))
			j++;
		while (!ft_isalpha(s2[i]) && !ft_isdigit(s2[i]))
			i++;
		if (s1[j] == s2[i])
		{
			j++;
			i++;
		}
		else
			return (s1[j] - s2[i]);
	}
	return (s1[j] - s2[i]);
}

int	strcmp_onlylowalph(const char *s1, const char *s2)
{
	int				j;
	int				i;

	j = 0;
	i = 0;
	while (s1[j] && s2[i])
	{
		while (!ft_isalpha(s1[j]) && !ft_isdigit(s1[j]))
			j++;
		while (!ft_isalpha(s2[i]) && !ft_isdigit(s2[i]))
			i++;
		if (ft_tolower(s1[j]) == ft_tolower(s2[i]))
		{
			j++;
			i++;
		}
		else
			return (ft_tolower(s1[j]) - ft_tolower(s2[i]));
	}
	return (ft_tolower(s1[j]) - ft_tolower(s2[i]));
}
