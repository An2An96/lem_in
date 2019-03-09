/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l5_find_best_comb_paths.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:21:05 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/06 22:18:26 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			get_steps_for_comb(t_path_comb *path_combs, int ants_count)
{
	int path_idx;
	int steps;
	int rest_ants;
	int res;
	int sum;

	steps = 0;
	rest_ants = 0;
	path_idx = path_combs->count - 1;
	while (path_idx >= 0)
	{
		sum = get_paths_diff(path_combs, path_idx);
		res = ((ants_count - rest_ants) - sum) / (path_idx + 1);
		steps += res;
		rest_ants += res * (path_idx + 1);
		path_idx--;
	}
	steps += path_combs->paths[0]->size - 1;
	return (steps);
}

/*
**	Выбор оптимальной комбинации путей для заданного числа муравьев
*/

t_path_comb	*choose_best_comb_paths(t_path_comb *path_combs)
{
	int cur_comb;
	int best_comb;
	int best_steps;

	best_comb = -1;
	cur_comb = 0;
	SET_MAX(best_steps);
	if (!path_combs[cur_comb].steps)
		return (NULL);
	while (path_combs[cur_comb].steps)
	{
		if (path_combs[cur_comb].steps < best_steps)
		{
			best_steps = path_combs[cur_comb].steps;
			best_comb = cur_comb;
		}
		cur_comb++;
	}
	return (&path_combs[best_comb]);
}
