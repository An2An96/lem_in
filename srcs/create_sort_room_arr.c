/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sort_room_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:56:25 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/20 18:58:33 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Создает массив вершин (комнат) сортируя по имени на этапе заполнения
*/

t_node **create_sort_room_arr(t_list *rooms_head, int count_rooms)
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
