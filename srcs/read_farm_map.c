/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_farm_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:47:35 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/19 17:37:00 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		add_edge(t_list	*rooms_head, char *parent_node_name, char *child_node_name)
{
	ft_printf("add_edge = %s -> %s\n", parent_node_name, child_node_name);
	
	t_node *parent;
	t_node *child;

	//	ищем адрес ноды родителя и дочернего элемента по имени
	//	!!! оптимизировать упорядочив список комнат по имени
	parent = NULL;
	child = NULL;
	while (rooms_head && (!parent || !child))
	{
		if (!ft_strcmp(((t_node*)rooms_head->content)->name, parent_node_name))
			parent = rooms_head->content;
		else if (!ft_strcmp(((t_node*)rooms_head->content)->name, child_node_name))
			child = rooms_head->content;
		rooms_head = rooms_head->next;
	}
	if (!parent || !child)
		return (0);
	ft_lstadd(&parent->childs, ft_lstnew(child, sizeof(child)));
	return (1);
}

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

static int		read_room_line(char *line, t_farm *farm)
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
			ft_printf("room %s: x = %s y = %s, status = %d\n", res[0], res[1], res[2], next_room_status);
			room = create_room(res[0],
				ft_atoi(res[1]), ft_atoi(res[2]), next_room_status);
			if (next_room_status == ROOM_START)
				farm->start = room;
			ft_lstadd(&farm->rooms, ft_lstnew(room, sizeof(room)));
			next_room_status = 0;
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

t_farm			*read_farm_map()
{
	char	*line;
	char	**res;
	char	read_status;
	int		lst_len;
	t_farm	*farm;

	farm = (t_farm*)malloc(sizeof(t_farm));
	farm->rooms = NULL;
	read_status = 0;
	while (get_next_line(0, &line))
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
				if (!read_room_line(line, farm))
					read_status = 2;
				else
					lst_len++;
			}
			if (read_status == 2)
			{
				res = ft_strsplit(line, '-');
				add_edge(farm->rooms, res[0], res[1]);
			}
		}
		free(line);
	}
	farm->ant_nodes = (int*)malloc(farm->ants_count * sizeof(int));
	return (farm);
}
