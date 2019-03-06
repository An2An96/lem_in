/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:20:50 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/06 20:28:01 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	debug_show_rooms(t_farm *farm)
{
	int i;

	i = 0;
	while (i < farm->count_rooms)
	{
		ft_printf("[DEBUG]: [%2d] -> %s\n", i, farm->rooms[i]->name);
		i++;
	}
	return (1);
}

int	debug_show_weights(t_farm *farm)
{
	int i;

	i = 0;
	while (i < farm->count_rooms)
	{
		ft_printf("[DEBUG]: room %s (%d) weight: %d\n",
			farm->rooms[i]->name, i, farm->rooms[i]->weight);
		i++;
	}
	return (1);
}

int	debug_show_paths(t_path_comb *paths_combs)
{
	int i;
	int j;

	i = 0;
	while (paths_combs[i].count)
	{
		ft_printf("[DEBUG]: %d comb (%d paths, %d steps):\n",
			i, paths_combs[i].count, paths_combs[i].steps);
		j = 0;
		while (paths_combs[i].paths[j])
		{
			show_path(paths_combs[i].paths[j]);
			j++;
		}
		i++;
	}
	return (1);
}
