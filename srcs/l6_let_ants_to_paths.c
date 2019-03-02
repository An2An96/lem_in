/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l6_let_ants_to_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:25:43 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/02 18:03:20 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	show_ant_pos(t_room *room)
{
	ft_printf("L%d-%s ", room->ant_num, room->name);
	// ft_printf("P%d-%s ", room->previous_ant, room->name);
}

static int	push_ants_along_path(t_path *path)
{
	t_node	*cur;
	t_room	*room;
	t_room	*prev_room;
	int		finished;

	finished = 0;
	cur = path->tail;
	while (cur && cur->prev)
	{
		room = (t_room*)cur->content;
		prev_room = (t_room*)cur->prev->content;
		if (room->ant_num == 0 && prev_room->ant_num != 0)
		{
			room->ant_num = prev_room->ant_num;
			prev_room->previous_ant = prev_room->ant_num;
			prev_room->ant_num = 0;
			show_ant_pos(room);
			if (path->tail == cur)
			{
				room->ant_num = 0;
				finished = 1;
			}
		}
		cur = cur->prev;
	}
	return (finished);
}

static void	choose_path_and_start(t_farm *farm, t_path **paths, int *nbr_ants)
{
	int		sum;
	int		path_idx;
	t_room	*room;

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
		room = (t_room*)paths[path_idx]->head->content;
		if (!room->ant_num)
		{
			room->ant_num = ++(*nbr_ants);
			show_ant_pos(room);
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
			push_ants_along_path(farm->best_paths[nbr_path]);
		nbr_path++;
	}
	if (nbr_ants < farm->ants_count)
		choose_path_and_start(farm, farm->best_paths, &nbr_ants);
	ft_printf("\n");
}

int			ft_close(void)
{
	exit(-1);
	return (0);
}

void		let_ants_to_paths(t_farm *farm)
{
// #ifdef DRAW_H
// 	if (farm->visualiser)
// 	{
// 		draw_farm(farm);
// 		mlx_hook(farm->visualiser->win_ptr, 17, 1L << 17, ft_close, NULL);
// 		mlx_key_hook(farm->visualiser->win_ptr, press_key_callback, farm);
// 		mlx_loop(farm->visualiser->mlx_ptr);
// 	}
// 	else
// 	{
// 		while (farm->finished_ants < farm->ants_count)
// 			make_step(farm);
// 	}
// #else
	while (farm->finished_ants < farm->ants_count)
		make_step(farm);
// #endif
}
