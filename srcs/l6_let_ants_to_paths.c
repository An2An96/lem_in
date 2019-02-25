/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l6_let_ants_to_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:25:43 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/25 19:47:45 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	show_ant_step(t_farm *farm, int room_idx)
{
	t_room *room;

	room = farm->rooms[room_idx];
	ft_printf("L%d-%s ", room->ant_num, room->name);
}

static int	push_ants_along_path(t_farm *farm, t_path *path)
{
	t_node	*cur;
	int		room_idx;
	int		prev_room_idx;
	int		finished;

	finished = 0;
	cur = path->tail;
	while (cur && cur->prev)
	{
		room_idx = *((int*)cur->content);
		prev_room_idx = *((int*)cur->prev->content);
		if (farm->rooms[room_idx]->ant_num == 0)
		{
			if (farm->rooms[prev_room_idx]->ant_num != 0)
			{
				farm->rooms[room_idx]->ant_num =
					farm->rooms[prev_room_idx]->ant_num;
				farm->rooms[prev_room_idx]->ant_num = 0;
				show_ant_step(farm, room_idx);
				if (path->tail == cur)
				{
					farm->rooms[room_idx]->ant_num = 0;
					finished = 1;
				}
			}
		}
		cur = cur->prev;
	}
	return (finished);
}

static void	choose_path_and_start(t_farm *farm, t_path **paths, int *nbr_ants)
{
	int sum;
	int path_idx;
	int room_idx;

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
		room_idx = *((int*)(paths[path_idx]->head->content));
		if (!farm->rooms[room_idx]->ant_num)
		{
			farm->rooms[room_idx]->ant_num = ++(*nbr_ants);
			show_ant_step(farm, room_idx);
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
#ifdef DRAW_H
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
#else
	while (farm->finished_ants < farm->ants_count)
		make_step(farm);
#endif
}
