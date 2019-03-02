/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l4_find_unique_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:11:32 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/02 20:23:06 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path		**find_unique_paths(t_farm *farm, int count)
{
	t_pqueue	*pqueue;
	t_room		*room;
	t_list		*neighbor_lst;
	t_room		*neighbor;
	int			complete_path;
	// t_path		*path;

	if (!(pqueue = pq_init(farm->count_rooms, true)))
		exit(-1);
	complete_path = 0;
	// path = ft_dlst_create();
	// farm->rooms[0]->path = path;
	// ft_dlst_push_back(path, ft_create_node_ptr(farm->rooms[0]));
	pq_insert(pqueue, farm->rooms[0], 1);
	while ((room = (t_room*)pq_extract(pqueue)))
	{
		ft_printf("extract room %s, weight: %d\n", room->name, room->weight);
		if (room == farm->rooms[farm->count_rooms - 1])
		{
			complete_path++;
			
			ft_printf("complete path %d!!!\n", complete_path);
			if (complete_path == count)
				return (NULL);
		}
		else
		{
			neighbor_lst = room->neighbors;
			while (neighbor_lst)
			{
				neighbor = farm->rooms[*(int*)neighbor_lst->content];
				ft_printf("insert room %s, weight: %d\n", neighbor->name, neighbor->weight);
				pq_insert(pqueue, neighbor, neighbor->weight);
				neighbor_lst = neighbor_lst->next;
			}
		}
	}
	return (NULL);
}
