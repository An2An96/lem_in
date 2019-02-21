/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_comb_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:21:05 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/21 18:40:47 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <math.h>

/*
**	Выбор оптимальной комбинации путей для заданного числа муравьев
*/

int	find_best_comb_paths(t_path ***path_combs, int ants_count)
{
	int	*count_step;
	int	n_route;
	int	i;
	int min;
	int	ret_n_route;
	int	len;

	len = 0;
	while (path_combs[len] != NULL)
		len++;
	count_step = ft_memalloc(len);
	n_route = 0;
	while (n_route < len)
	{
		i = 0;
		count_step[n_route] = 0;
		while (i <= n_route)
		{
			count_step[n_route] = MAX(
				path_combs[n_route][i]->count_node + floor(ants_count / (n_route + 1)),
				count_step[n_route]);
			i++;
		}
		n_route++;
	}
	i = 0;
	min = count_step[i];
	ret_n_route = i;
	while (i < n_route)
	{
		int k = count_step[i];
		if (count_step[i] < min)
		{
			min = count_step[i];
			ret_n_route = i;
		}
		i++;
	}
	free(count_step);
	return (ret_n_route);
}
