/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l5_find_best_comb_paths.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:21:05 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/25 17:10:38 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	get_steps_for_comb(
	t_path **path_combs, int path_counts, int ants_count)
{
	int path_idx;
	int steps;
	int rest_ants;
	int res;
	int sum;

	steps = 0;
	rest_ants = 0;
	path_idx = path_counts - 1;
	while (path_idx >= 0)
	{
		sum = get_paths_diff(path_combs, path_idx);
		res = ((ants_count - rest_ants) - sum) / (path_idx + 1);
		steps += res;
		rest_ants += res * (path_idx + 1);
		path_idx--;
	}
	steps += path_combs[0]->size - 1;
	return (steps);
}

/*
**	Выбор оптимальной комбинации путей для заданного числа муравьев
*/

int			find_best_comb_paths(t_path ***path_combs, int ants_count)
{
	int cur_comb;
	int cur_steps;
	int best_comb;
	int best_steps;

	cur_comb = 0;
	best_steps = INT_MAX;
	while (path_combs[cur_comb])
	{
		cur_steps =
			get_steps_for_comb(path_combs[cur_comb], cur_comb + 1, ants_count);
		if (cur_steps < best_steps)
		{
			best_steps = cur_steps;
			best_comb = cur_comb;
		}
		cur_comb++;
	}
	return (best_comb);
}
