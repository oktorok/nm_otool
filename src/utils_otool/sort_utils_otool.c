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

#include "ft_otool.h"

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
