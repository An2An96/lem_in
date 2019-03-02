/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l6_let_ants_to_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:25:43 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/02 21:48:09 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline static void	show_ant_pos(t_room *room)
{
	write(1, "L", 1);
	ft_putnbr(room->ant_num);
	write(1, "-", 1);
	ft_putstr(room->name);
	write(1, " ", 1);
}

static int			push_ants_along_path(t_path *path)
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

static void			choose_path_and_start(
	t_farm *farm, t_path **paths, int *nbr_ants)
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

void				make_step(t_farm *farm)
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

void				let_ants_to_paths(t_farm *farm)
{
	int	nbr_ants;
	int	nbr_path;

	nbr_ants = 0;
	while (farm->finished_ants < farm->ants_count)
	{
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
}
