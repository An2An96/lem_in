/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l2_create_sort_room_arr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:56:25 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/22 20:34:36 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	insert_item(t_node **rooms, t_node *room, int count_rooms)
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

t_node		**create_sort_room_arr(t_list *rooms_head, int count_rooms)
{
	int		i;
	t_list	*cur;
	t_node	**rooms;

	if (!(rooms = (t_node**)malloc((count_rooms + 1) * sizeof(t_node*))))
		exit(-1);
	i = 0;
	while (i < (count_rooms + 1))
		rooms[i++] = NULL;
	cur = rooms_head;
	while (cur)
	{
		if (((t_node*)(cur->content))->status == ROOM_START)
			rooms[0] = (t_node*)(cur->content);
		else if (((t_node*)(cur->content))->status == ROOM_END)
			rooms[count_rooms - 1] = (t_node*)(cur->content);
		else
			insert_item(rooms, (t_node*)(cur->content), count_rooms);
		cur = cur->next;
	}
	return (rooms);
}
