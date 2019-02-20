/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_farm_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:47:35 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/20 18:18:53 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		add_edge(
	t_node	**rooms, int8_t** incidence, char *parent_name, char *child_name)
{
	int parent_idx;
	int child_idx;

	// ft_printf("add_edge = %s -> %s\n", parent_name, child_name);

	parent_idx = find_node_index_by_name(rooms, parent_name);
	child_idx = find_node_index_by_name(rooms, child_name);

	// ft_printf("%s -> %d\n", parent_name, parent_idx);
	// ft_printf("%s -> %d\n", child_name, child_idx);

	incidence[parent_idx][child_idx] = 1;
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

t_node **create_assoc_sort_room_arr(t_list *rooms_head, int count_rooms)
{
	int		i;
	int		res;
	int		inserted;
	t_list	*cur;
	t_node	**rooms_arr;

	rooms_arr = (t_node**)malloc((count_rooms + 1) * sizeof(t_node*));
	i = 0;
	while (i < count_rooms)
		rooms_arr[i++] = NULL;
	cur = rooms_head;
	while (cur)
	{
		if (((t_node*)(cur->content))->status == ROOM_START)
			rooms_arr[0] = (t_node*)(cur->content);
		else if (((t_node*)(cur->content))->status == ROOM_END)
			rooms_arr[count_rooms - 1] = (t_node*)(cur->content);
		else
		{
			i = count_rooms - 2;
			inserted = 0;
			while (i > 0)
			{
				if (rooms_arr[i])
				{
					res = ft_strcmp(rooms_arr[i]->name, ((t_node*)(cur->content))->name);
					if (res > 0)
						rooms_arr[i + 1] = rooms_arr[i];
					else
					{
						rooms_arr[i + 1] = (t_node*)(cur->content);
						inserted = 1;
						break ;
					}
				}
				i--;
			}
			if (!inserted)
				rooms_arr[1] = (t_node*)(cur->content);
		}
		cur = cur->next;
	}
	return (rooms_arr);
}

int8_t**	create_incidence_matrix(int count_rooms)
{
	int i;
	int j;
	int8_t	**matrix;

	matrix = (int8_t**)malloc(count_rooms * sizeof(int8_t*));
	i = 0;
	while (i < count_rooms)
	{
		j = 0;
		matrix[i] = (int8_t*)malloc(count_rooms * sizeof(int8_t));
		while (j < count_rooms)
		{
			matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	return (matrix);
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

void	show_incidence_matrix(t_node **rooms, int8_t **incidence, int size)
{
	int i;
	int j;

	i = -1;
	ft_printf("       ");
	while (++i < size)
		ft_printf(" %5s", rooms[i]->name);
	ft_printf("\n");
	i = -1;
	ft_printf("       __________________________________________________________________\n");
	i = 0;
	while (i < size)
	{
		j = 0;
		ft_printf("%5s |", rooms[i]->name);
		while (j < size)
		{
			ft_printf(" %5d", incidence[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("      |__________________________________________________________________\n");
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
					rooms_arr = create_assoc_sort_room_arr(rooms, count_rooms);
					int i = 0;
					while (i < count_rooms)
					{
						ft_printf("%d - %s\n", i, rooms_arr[i]->name);
						i++;
					}
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
