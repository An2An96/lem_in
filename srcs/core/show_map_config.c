/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:36:09 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/08 16:22:37 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline static void	show_rooms(t_room **rooms, int count_rooms)
{
	int i;

	i = 0;
	while (i < count_rooms)
	{
		if (rooms[i]->types & ROOM_START)
			write(1, "##start\n", 8);
		if (rooms[i]->types & ROOM_END)
			write(1, "##end\n", 6);
		ft_putstr(rooms[i]->name);
		write(1, " ", 1);
		ft_putnbr(rooms[i]->x);
		write(1, " ", 1);
		ft_putnbr(rooms[i]->y);
		write(1, "\n", 1);
		i++;
	}
}

inline static void	show_edges(t_room **rooms, int count_rooms)
{
	int		i;
	t_list	*neighbor_lst;
	int		neighbor_idx;

	i = 0;
	while (i < count_rooms)
	{
		neighbor_lst = rooms[i]->neighbors;
		while (neighbor_lst)
		{
			neighbor_idx = *LIST(neighbor_lst, int*);
			if (neighbor_idx > i)
			{
				ft_putstr(rooms[i]->name);
				write(1, "-", 1);
				ft_putstr(rooms[neighbor_idx]->name);
				write(1, "\n", 1);
			}
			neighbor_lst = neighbor_lst->next;
		}
		i++;
	}
}

void				show_map_config(t_farm *farm)
{
	ft_putnbr(farm->ants_count);
	write(1, "\n", 1);
	show_rooms(farm->rooms, farm->count_rooms);
	show_edges(farm->rooms, farm->count_rooms);
	write(1, "\n", 1);
}
