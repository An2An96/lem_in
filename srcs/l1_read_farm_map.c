/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l1_read_farm_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:47:35 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/26 15:14:24 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*create_room(char *name, int x, int y, int type)
{
	t_room	*room;

	if ((room = (t_room*)ft_memalloc(sizeof(t_room))))
	{
		room->name = ft_strdup(name);
		room->x = x;
		room->y = y;
		room->type = type;
	}
	return (room);
}

/*
**	Делает смежными два узла
*/

static int		add_edge(t_farm *farm, char *parent_name, char *child_name)
{
	t_room	*parent;
	t_room	*child;

	parent = find_node_by_name(farm->rooms, parent_name);
	child = find_node_by_name(farm->rooms, child_name);
	if (!parent || !child)
		return (0);
	if (parent == farm->rooms[0])
		farm->start_edges++;
	if (child == farm->rooms[farm->count_rooms - 1])
		farm->finish_edges++;
	t_list *t = ft_lstnew_ptr((void*)child);
	ft_lstpush(&parent->childs, t);
	return (1);
}

static int		parse_room_line(char *line, t_list **rooms, int *count_rooms)
{
	static int8_t	next_room_type;
	char			**res;
	t_room			*room;

	if (!ft_strcmp(line, "##start"))
		next_room_type = ROOM_START;
	else if (!ft_strcmp(line, "##end"))
		next_room_type = ROOM_END;
	else
	{
		res = ft_strsplit(line, ' ');
		if (res[0] && res[1] && res[2] && !res[3])
		{
			room = create_room(res[0],
				ft_atoi(res[1]), ft_atoi(res[2]), next_room_type);
			ft_lstadd(rooms, ft_lstnew(room, sizeof(t_room)));
			free(room);
			next_room_type = 0;
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
	int8_t	read_status;
	t_farm	*farm;
	t_list	*rooms;

	if (!(farm = (t_farm*)ft_memalloc(sizeof(t_farm))))
		exit(-1);
	rooms = NULL;
	read_status = 0;
	while (get_next_line(fd, &line))
	{
		if (read_status == 0 && ++read_status)
			farm->ants_count = ft_atoi(line);
		else
		{
			if (read_status == 1)
			{
				if (!parse_room_line(line, &rooms, &farm->count_rooms))
				{
					read_status = 2;
					farm->rooms =
						create_sort_room_arr(rooms, farm->count_rooms);
					ft_lstdel(&rooms, NULL);
				}
			}
			if (read_status == 2)
			{
				res = ft_strsplit(line, '-');
				if (res[0] && res[1] && !res[2])
					if (!add_edge(farm, res[0], res[1]))
						exit(-1);
				free_split_result(res);
			}
		}
		free(line);
	}
	return (farm);
}
