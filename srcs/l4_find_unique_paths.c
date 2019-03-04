/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l4_find_unique_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:11:32 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/04 18:03:51 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	show_path_(t_path *path)
{
	t_node	*cur;

	if (path)
	{
		cur = path->head;
		while (cur)
		{
			ft_printf("%s ", ((t_room*)cur->content)->name);
			cur = cur->next;
		}
		ft_printf("\n");
	}
}

int			find_cycle(t_path *path, t_room *room)
{
	t_node	*cur;

	if (path)
	{
		cur = path->head;
		while (cur)
		{
			if ((t_room*)cur->content == room)
				return (true);
			cur = cur->next;
		}
	}
	return (false);
}

t_path		*path_copy(t_path *path)
{
	t_path	*new;
	t_node	*cur;

	// ft_printf("original:\n");
	// show_path_(path);
	if (path)
	{
		if (!(new = ft_dlst_create()))
			return (NULL);
		cur = path->head;
		while (cur)
		{
			ft_dlst_push_back(new, ft_create_node_ptr(cur->content));
			cur = cur->next;
		}
		// ft_printf("copy:\n");
		// show_path_(new);
	}
	return (new);
}

void		path_selection(t_farm *farm, t_room *room, t_pqueue	*pqueue)
{
	ft_printf("\n\nenter room %s (%d %d %d %d %d)\n", room->name,
		room->processed_paths[0], room->processed_paths[1],
		room->processed_paths[2], room->processed_paths[3],
		room->processed_paths[4]);

	t_list	*path_lst;
	t_list	*neighbor_lst;
	t_path	*path;
	t_room	*neighbor;
	bool	original_path_lst_usage;
	int		i;

	i = 0;
	path_lst = room->paths;
	while (path_lst)
	{
		original_path_lst_usage = false;
		path = (t_path*)path_lst->content;
		if (!room->processed_paths[i])
		{
			ft_dlst_push_back(path, ft_create_node_ptr(room));
			neighbor_lst = room->neighbors;
			while (neighbor_lst)
			{
				neighbor = farm->rooms[*(int*)neighbor_lst->content];
				if (!find_cycle(path, neighbor))
				// if (!path->tail
				// 	|| !path->tail->prev
				// 	|| (t_room*)path->tail->prev->content != neighbor)
				{
					if (!original_path_lst_usage)
					{
						ft_printf("throw path to %s\n", neighbor->name);
						show_path_(path);
						ft_lstadd(&neighbor->paths, ft_lstnew_ptr(path));
						original_path_lst_usage = true;
					}
					else
					{
						ft_printf("copy and throw path to %s\n", neighbor->name);
						show_path_(path);
						ft_lstadd(&neighbor->paths, ft_lstnew_ptr(path_copy(path)));
					}
					pq_insert(pqueue, neighbor, neighbor->weight);
				}
				neighbor_lst = neighbor_lst->next;
			}
			room->processed_paths[i] = true;
		}
		i++;
		path_lst = path_lst->next;
	}
	ft_printf("\n\n");
}

t_path		**find_unique_paths(t_farm *farm, int count)
{
	t_pqueue	*pqueue;
	t_room		*room;
	t_list		*neighbor_lst;
	t_room		*neighbor;
	int			complete_path;
	t_path		*path;
	int			i;
	t_list		*path_lst;

	if (!(pqueue = pq_init(farm->count_rooms, true)))
		exit(-1);
	complete_path = 0;


	for (int i = 0; i < farm->count_rooms; i++)
	{
		for (int j = 0; j < 10; j++)
			ft_printf("%d", farm->rooms[i]->processed_paths[j]);
		ft_printf("\n");
	}
		

	if (!(path = ft_dlst_create()))
		exit(-1);
	// ft_dlst_push_back(path, ft_create_node_ptr(farm->rooms[0]));
	ft_lstadd(&farm->rooms[0]->paths, ft_lstnew_ptr(path));
	pq_insert(pqueue, farm->rooms[0], 0);
	while ((room = (t_room*)pq_extract(pqueue)))
	{
		ft_printf("extract room %s, weight: %d\n", room->name, room->weight);
		if (room == farm->rooms[farm->count_rooms - 1])
		{
			complete_path++;
			
			ft_printf("complete path %d!!!\n", complete_path);

			t_list *path_lst = room->paths;
			while (path_lst)
			{
				ft_printf("%p ", path_lst);
				show_path_((t_path*)path_lst->content);
				path_lst = path_lst->next;
			}

			if (complete_path == count)
				return (NULL);
		}
		else
		{
			i = 0;
			neighbor_lst = room->neighbors;
			// path_lst = ft_lstget(room->paths, room->processed_paths);

			path_selection(farm, room, pqueue);

			// while (neighbor_lst)
			// {
			// 	neighbor = farm->rooms[*(int*)neighbor_lst->content];

			// 	ft_printf("insert room %s, weight: %d\n", neighbor->name, neighbor->weight);
			// 	pq_insert(pqueue, neighbor, neighbor->weight);
			// 	neighbor_lst = neighbor_lst->next;
			// }
		}
	}
	return (NULL);
}
