/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l1_read_farm_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:47:35 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/06 15:47:02 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*create_room(char *name, int x, int y, int8_t type)
{
	int		i;
	t_room	*room;

	if (name[0] == 'L' || ft_strstr(name, "-"))
		throw_error(STR_ERROR_VALID, "Forbidden room name");
	SECURE_MALLOC(room = (t_room*)ft_memalloc(sizeof(t_room)));
	room->name = ft_strdup(name);
	room->x = x;
	room->y = y;
	room->types = type;
	room->weight = -1;
	room->paths = ft_dlst_create();
	i = 0;
	while (i < 100)		//	FIX IT!!!
	{
		room->processed_paths[i] = 0;
		i++;
	}
	return (room);
}

/*
**	Делает смежными два узла
*/

static int		add_edge(t_farm *farm, char *parent_name, char *child_name)
{
	int		parent;
	int		child;
	t_list	*el;

	parent = find_node_index_by_name(farm->rooms, farm->count_rooms, parent_name);
	child = find_node_index_by_name(farm->rooms, farm->count_rooms, child_name);
	if (parent == -1 || child == -1)
		return (0);
	if (parent == 0 || child == 0)
		farm->start_edges++;
	if (parent == farm->count_rooms - 1 || child == farm->count_rooms - 1)
		farm->finish_edges++;
	el = ft_lstnew((void*)&child, sizeof(child));
	ft_lstpush(&farm->rooms[parent]->neighbors, el);
	el = ft_lstnew((void*)&parent, sizeof(child));
	ft_lstpush(&farm->rooms[child]->neighbors, el);
	return (1);
}

static int		parse_room_line(char *line, t_list **rooms, int *count_rooms)
{
	static int8_t	next_room_type;
	char			**res;
	t_room			*room;

	if (!ft_strcmp(line, "##start"))
		next_room_type |= ROOM_START;
	else if (!ft_strcmp(line, "##end"))
		next_room_type |= ROOM_END;
	else
	{
		res = ft_strsplit(line, ' ');
		if (res[0] && res[1] && res[2] && !res[3])
		{
			room = create_room(res[0],
				min_atoi(res[1]), min_atoi(res[2]), next_room_type);
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

t_farm			*read_farm_map(int fd, t_farm *farm)
{
	char	*line;
	char	**res;
	int8_t	read_status;
	t_list	*rooms;

	rooms = NULL;
	read_status = 0;
	while (get_next_line(fd, &line))
	{
		if (line[0] == '#' && line[1] != '#')
		{
			free(line);
			continue ;
		}
		if (read_status == 0 && ++read_status)
		{
			if (ft_isdigit(line[0]))
				farm->ants_count = ft_atoi(line);
			else
				throw_error(STR_ERROR_VALID, "No ants");
		}
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
					!add_edge(farm, res[0], res[1]) && throw_error(STR_ERROR_VALID, "Attempt to create edge for a non-existent room");
				free_split_result(res);
			}
		}
		free(line);
	}
	if (read_status < 1)
		throw_error(STR_ERROR_VALID, "Map contains insufficient data");
	if (!farm->rooms && rooms)
	{
		farm->rooms = create_sort_room_arr(rooms, farm->count_rooms);
		ft_lstdel(&rooms, NULL);
	}
	return (farm);
}
