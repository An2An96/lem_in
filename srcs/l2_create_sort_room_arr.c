/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l2_create_sort_room_arr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:56:25 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/08 13:53:09 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			insert_item(t_room **rooms, t_room *room, int count_rooms)
{
	int i;
	int inserted;

	i = count_rooms - 2;
	inserted = 0;
	while (i > 0)
	{
		if (rooms[i])
		{
			if (ft_strcmp(rooms[i]->name, room->name) > 0)
				rooms[i + 1] = rooms[i];
			else
			{
				rooms[i + 1] = room;
				inserted = 1;
				break ;
			}
		}
		i--;
	}
	if (!inserted)
		rooms[1] = room;
}

static int			append_room_in_arr(
	t_room **room_arr, int count_rooms, t_room *room)
{
	if (room->types)
	{
		if (room->types & ROOM_START)
			room_arr[0] = room;
		if (room->types & ROOM_END)
			room_arr[count_rooms - 1] = room;
	}
	else
		insert_item(room_arr, room, count_rooms);
	return (room->types);
}

inline static void	check_duplicate_start_end(
	bool *find_start, bool *find_end, int room_types)
{
	if (*find_start)
		(room_types & ROOM_START)
			&& throw_error(STR_ERROR_VALID, "Duplicate start");
	else
		*find_start = room_types & ROOM_START;
	if (*find_end)
		(room_types & ROOM_END)
			&& throw_error(STR_ERROR_VALID, "Duplicate end");
	else
		*find_end = room_types & ROOM_END;
}

/*
**	Создает массив вершин (комнат) сортируя по имени на этапе заполнения
*/

t_room				**create_sort_room_arr(t_list **rooms_head, int count_rooms)
{
	t_list	*cur;
	t_room	**rooms;
	bool	find_start;
	bool	find_end;
	int		room_types;

	find_start = false;
	find_end = false;
	SECURE_MALLOC(rooms =
		(t_room**)ft_memalloc((count_rooms + 1) * sizeof(t_room*)));
	cur = *rooms_head;
	while (cur)
	{
		room_types = append_room_in_arr(rooms, count_rooms, LIST(cur, t_room*));
		check_duplicate_start_end(&find_start, &find_end, room_types);
		cur = cur->next;
	}
	!find_start && throw_error(STR_ERROR_VALID, "No start");
	!find_end && throw_error(STR_ERROR_VALID, "No end");
	ft_lstdel(rooms_head, NULL);
	return (rooms);
}
