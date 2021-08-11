/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:06:11 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/24 04:33:48 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	quicksort_alpha(t_sort *sort, unsigned long start_end[2],
						int (*f)(const char *, const char *))
{
	unsigned long	i;
	unsigned long	j;
	int				t;

	j = start_end[0] - 1;
	i = start_end[0];
	if ((long)start_end[0] > (long)start_end[1])
		return ;
	while (i < start_end[1])
	{
		t = f((char *)sort[i].name, (char *)sort[start_end[1]].name);
		if (t < 0)
			swap_value(sort + ++j, sort + i);
		else if (!t && (sort[i].value < sort[start_end[1]].value))
			swap_value(sort + ++j, sort + i);
		i++;
	}
	swap_value(sort + (j + 1), sort + start_end[1]);
	quicksort_alpha(sort, (unsigned long [2]){start_end[0], j}, f);
	quicksort_alpha(sort, (unsigned long [2]){j + 2, start_end[1]}, f);
}

static void	quicksort_num(t_sort *sort, unsigned long start_end[2],
						int (*f)(const int, const int))
{
	unsigned long	i;
	unsigned long	j;
	int				t;

	j = start_end[0] - 1;
	i = start_end[0];
	if ((long)start_end[0] > (long)start_end[1])
		return ;
	while (i < start_end[1])
	{
		t = f(sort[i].value, sort[start_end[1]].value);
		if (t > 0)
			swap_value(sort + ++j, sort + i);
		i++;
	}
	swap_value(sort + (j + 1), sort + start_end[1]);
	quicksort_num(sort, (unsigned long [2]){start_end[0], j}, f);
	quicksort_num(sort, (unsigned long [2]){j + 2, start_end[1]}, f);
}

t_sort	*order_symb_alpha(t_sort *sort, unsigned long symlen, char slash)
{
	if (get_flags("-reverse-sort"))
		quicksort_alpha(sort, (unsigned long [2]){0, symlen - 1}, strcmp_onlylowalph_reverse);
	else if (!slash)
		quicksort_alpha(sort, (unsigned long [2]){0, symlen - 1}, strcmp_onlylowalph);
	else if (slash == NO_SLASH_ALPHA)
		quicksort_alpha(sort, (unsigned long [2]){0, symlen - 1}, strcmp_onlyalph);
	else
		quicksort_alpha(sort, (unsigned long [2]){0, symlen - 1}, ft_strcmp);
	return (sort);
}

t_sort	*order_objects_offset(t_sort *sort, unsigned long objnum)
{
	quicksort_num(sort, (unsigned long [2]){0, objnum - 1}, ft_max_sort);
	return (sort);
}
