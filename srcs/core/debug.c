/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:20:50 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/09 16:46:46 by rschuppe         ###   ########.fr       */
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

int	debug_show_path(t_path *path)
{
	t_node	*cur;

	cur = path->head;
	while (cur)
	{
		ft_printf("%s%s",
			cur != path->head ? " -> " : "", ((t_room*)cur->content)->name);
		cur = cur->next;
	}
	ft_printf("\n");
	return (1);
}

int	debug_show_comb(t_path_comb *path_comb)
{
	int i;

	i = -1;
	while (path_comb->paths[++i])
		debug_show_path(path_comb->paths[i]);
	return (1);
}

int	debug_show_paths_combs(t_path_comb *paths_combs)
{
	int i;
	int j;

	i = 0;
	while (paths_combs[i].count)
	{
		ft_printf("[DEBUG]: %d comb (%d paths, %d steps):\n",
			i, paths_combs[i].count, paths_combs[i].steps);
		j = 0;
		debug_show_comb(&paths_combs[i]);
		i++;
	}
	return (1);
}

int	debug_show_matrix(bool **matrix, int size)
{
	int i;
	int j;

	i = 0;
	ft_printf("\n");
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_printf("%d", matrix[i][j]);
			j++;
		}
		i++;
		ft_printf("\n");
	}
	ft_printf("\n");
	return (1);
}
