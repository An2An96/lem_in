/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_farm_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:47:35 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/20 19:06:28 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_node	*create_room(char *name, int x, int y, int status)
{
	t_node	*room;

	room = (t_node*)malloc(sizeof(t_node));
	room->name = ft_strdup(name);
	room->x = x;
	room->y = y;
	room->status = status;
	return (room);
}

static void		free_split_result(char **res)
{
	int i;

	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);
}

static int		read_room_line(char *line, t_list **rooms, int *count_rooms)
{
	static char next_room_status;
	char		**res;
	t_node		*room;

	if (!ft_strcmp(line, "##start"))
		next_room_status = ROOM_START;
	else if (!ft_strcmp(line, "##end"))
		next_room_status = ROOM_END;
	else
	{
		res = ft_strsplit(line, ' ');
		if (res[0] && res[1] && res[2] && !res[3])
		{
			room = create_room(res[0],
				ft_atoi(res[1]), ft_atoi(res[2]), next_room_status);
			ft_lstadd(rooms, ft_lstnew(room, sizeof(t_node)));
			free(room);
			next_room_status = 0;
			(*count_rooms)++;
		}
		else
		{
			free_split_result(res);
			return (0);
		}
		free_split_result(res);
	}
	return (1);
}

t_farm			*read_farm_map(int fd)
{
	char	*line;
	char	**res;
	char	read_status;
	int		count_rooms;

	t_farm	*farm;
	t_list	*rooms;
	t_node	**rooms_arr;

	farm = (t_farm*)malloc(sizeof(t_farm));
	count_rooms = 0;
	rooms = NULL;
	read_status = 0;
	while (get_next_line(fd, &line))
	{
		if (read_status == 0)
		{
			farm->ants_count = ft_atoi(line);
			read_status++;
		}
		else
		{
			if (read_status == 1)
			{
				if (!read_room_line(line, &rooms, &count_rooms))
				{
					read_status = 2;
					rooms_arr = create_sort_room_arr(rooms, count_rooms);
					ft_lstdel(&rooms, NULL);
					// int i = 0;
					// while (i < count_rooms)
					// {
					// 	ft_printf("%d - %s\n", i, rooms_arr[i]->name);
					// 	i++;
					// }
					farm->incidence = create_incidence_matrix(count_rooms);
				}
			}
			if (read_status == 2)
			{
				res = ft_strsplit(line, '-');
				add_edge(rooms_arr, farm->incidence, res[0], res[1]);
			}
		}
		free(line);
	}
	show_incidence_matrix(rooms_arr, farm->incidence, count_rooms);
	return (farm);
}
