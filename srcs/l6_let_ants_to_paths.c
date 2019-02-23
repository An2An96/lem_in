/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l6_let_ants_to_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:25:43 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/23 19:32:34 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	show_ant_step(t_farm *farm, int room_idx)
{
	t_node *room;

	room = farm->rooms[room_idx];
	ft_printf("L%d-%s ", room->ant_num, room->name);
}

static int	push_ants_along_path(t_farm *farm, t_path *path)
{
	int pos;
	int finished;

	finished = 0;
	pos = path->count_node - 1;
	while (pos > 0)
	{
		if (farm->rooms[path->idx[pos]]->ant_num == 0)
		{
			if (farm->rooms[path->idx[pos - 1]]->ant_num != 0)
			{
				farm->rooms[path->idx[pos]]->ant_num =
					farm->rooms[path->idx[pos - 1]]->ant_num;
				farm->rooms[path->idx[pos - 1]]->ant_num = 0;
				show_ant_step(farm, path->idx[pos]);
				if (pos == path->count_node - 1)
				{
					farm->rooms[path->idx[pos]]->ant_num = 0;
					finished = 1;
				}
			}
		}
		pos--;
	}
	return (finished);
}

static void	choose_path_and_start(t_farm *farm, t_path **paths, int *nbr_ants)
{
	int sum;
	int path_idx;

	path_idx = 0;
	while (paths[path_idx] && *nbr_ants < farm->ants_count)
	{
		if (path_idx > 0)
		{
			sum = 0;
			sum += get_paths_diff(paths, path_idx);
			if (sum >= (farm->ants_count - *nbr_ants))
				break ;
		}
		if (!farm->rooms[paths[path_idx]->idx[0]]->ant_num)
		{
			farm->rooms[paths[path_idx]->idx[0]]->ant_num = ++(*nbr_ants);
			show_ant_step(farm, paths[path_idx]->idx[0]);
		}
		path_idx++;
	}
}

void		make_step(t_farm *farm)
{
	static int	nbr_ants;
	int			nbr_path;

	nbr_path = 0;
	while (farm->best_paths[nbr_path])
	{
		farm->finished_ants +=
			push_ants_along_path(farm, farm->best_paths[nbr_path]);
		nbr_path++;
	}
	if (nbr_ants < farm->ants_count)
		choose_path_and_start(farm, farm->best_paths, &nbr_ants);
	ft_printf("\n");
}

void		let_ants_to_paths(t_farm *farm)
{
	if (farm->visualiser)
	{
		mlx_hook(farm->visualiser->win_ptr, 17, 1L << 17, ft_close, NULL);
		mlx_key_hook(farm->visualiser->win_ptr, press_key_callback, farm);
		mlx_loop(farm->visualiser->mlx_ptr);
	}
	else
	{
		while (farm->finished_ants < farm->ants_count)
			make_step(farm);
	}
}
