/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l2_create_sort_room_arr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:56:25 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/25 17:28:20 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	insert_item(t_room **rooms, t_room *room, int count_rooms)
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

/*
**	Создает массив вершин (комнат) сортируя по имени на этапе заполнения
*/

t_room		**create_sort_room_arr(t_list *rooms_head, int count_rooms)
{
	int		i;
	t_list	*cur;
	t_room	**rooms;

	if (!(rooms = (t_room**)malloc((count_rooms + 1) * sizeof(t_room*))))
		exit(-1);
	i = 0;
	while (i < (count_rooms + 1))
		rooms[i++] = NULL;
	cur = rooms_head;
	while (cur)
	{
		if (((t_room*)(cur->content))->status == ROOM_START)
			rooms[0] = (t_room*)(cur->content);
		else if (((t_room*)(cur->content))->status == ROOM_END)
			rooms[count_rooms - 1] = (t_room*)(cur->content);
		else
			insert_item(rooms, (t_room*)(cur->content), count_rooms);
		cur = cur->next;
	}
	return (rooms);
}
