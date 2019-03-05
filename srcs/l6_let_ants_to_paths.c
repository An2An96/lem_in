/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l6_let_ants_to_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:25:43 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/05 20:41:45 by rschuppe         ###   ########.fr       */
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
	t_farm *farm, t_path_comb *path_comb, int *nbr_ants)
{
	int		sum;
	int		path_idx;
	t_room	*room;

	path_idx = 0;
	while (path_comb->paths[path_idx] && *nbr_ants < farm->ants_count)
	{
		if (path_idx > 0)
		{
			sum = 0;
			sum += get_paths_diff(path_comb, path_idx);
			if (sum >= (farm->ants_count - *nbr_ants))
				break ;
		}
		room = LIST(path_comb->paths[path_idx]->head, t_room*);
		// if (!room->ant_num)
		// {
		if (room->type == ROOM_END)
			farm->finished_ants++;
		room->ant_num = ++(*nbr_ants);
		show_ant_pos(room);
		// }
		path_idx++;
	}
}

void				let_ants_to_paths(t_farm *farm, t_path_comb *path_comb)
{
	int	nbr_ants;
	int	nbr_path;

	if (!path_comb)
	{
		write(1, "Error: no way to the finish\n", 28);
		return ;
	}

	ft_printf("Best paths comb:\n");
	int i = -1;
	while (path_comb->paths[++i])
		show_path(path_comb->paths[i]);
	ft_printf("\n");

	nbr_ants = 0;
	while (farm->finished_ants < farm->ants_count)
	{
		nbr_path = 0;
		while (path_comb->paths[nbr_path])
		{
			farm->finished_ants +=
				push_ants_along_path(path_comb->paths[nbr_path]);
			nbr_path++;
		}
		if (nbr_ants < farm->ants_count)
			choose_path_and_start(farm, path_comb, &nbr_ants);
		write(1, "\n", 1);
	}
}
