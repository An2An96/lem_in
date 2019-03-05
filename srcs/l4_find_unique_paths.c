/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l4_find_unique_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:11:32 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/05 13:37:34 by rschuppe         ###   ########.fr       */
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

	// ft_printf("\n[find_cycle]\nroom: %s\npath: ", room->name);
	cur = path->head;
	// while (cur)
	// {
	// 	ft_printf("%s -> ", ((t_room*)cur->content)->name);
	// 	cur = cur->next;
	// }
	// ft_printf("\n");
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
	}
	return (new);
}

void		path_selection(t_farm *farm, t_room *room, int old_priority, t_pqueue *pqueue)
{
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
		// ft_printf("\x1b[1;31mCheck path %d\x1b[0m\n", i);
		show_path_(path);
		if (!room->processed_paths[i])
		{
			// ft_printf("\x1b[32;01mNot processed\x1b[0m\n");
			ft_dlst_push_back(path, ft_create_node_ptr(room));
			neighbor_lst = room->neighbors;
			while (neighbor_lst)
			{
				neighbor = farm->rooms[*(int*)neighbor_lst->content];
				if (!find_cycle(path, neighbor))
				{
					if (!original_path_lst_usage)
					{
						// ft_printf("throw path to %s\n", neighbor->name);
						// show_path_(path);
						ft_lstpush(&neighbor->paths, ft_lstnew_ptr(path));
						original_path_lst_usage = true;
					}
					else
					{
						// ft_printf("copy and throw path to %s\n", neighbor->name);
						// show_path_(path);
						ft_lstpush(&neighbor->paths, ft_lstnew_ptr(path_copy(path)));
					}
					if (neighbor->type == ROOM_END)
						pq_insert(pqueue, neighbor, 0);
					else
						pq_insert(pqueue, neighbor, old_priority + neighbor->weight);
				}
				neighbor_lst = neighbor_lst->next;
			}
			room->processed_paths[i] = true;
		}
		i++;
		path_lst = path_lst->next;
	}
	// ft_printf("\n\n");
}

t_path		***allocate_mem_for_paths_combs(int count)
{
	int		i;
	t_path	***paths_combs;

	i = 0;
	paths_combs = (t_path***)ft_memalloc(sizeof(t_path**));
	while (i < count)
	{
		paths_combs[i] = (t_path**)ft_memalloc((i + 1) * sizeof(t_path*));
		i++;
	}
	return (paths_combs);
}

/*
**	Хранение списков заменить на двусвязный список для более быстрого добалвения
**	В конец
*/

t_path		**find_unique_paths(t_farm *farm, int count)
{
	t_pqueue	*pqueue;
	t_room		*room;
	t_path		*path;
	// t_list		*path_lst;
	int			priority;
	t_path		***paths_combs;
	t_path		**result;

	paths_combs = allocate_mem_for_paths_combs(count);

	if (!(pqueue = pq_init(farm->count_rooms, true)))
		exit(-1);
	if (!(path = ft_dlst_create()))
		exit(-1);
	ft_lstadd(&farm->rooms[0]->paths, ft_lstnew_ptr(path));
	pq_insert(pqueue, farm->rooms[0], 0);
	while ((room = (t_room*)pq_extract_ex(pqueue, &priority)))
	{
		ft_printf("\x1b[0;33mextract room %s [%d], weight: %d\x1b[0m\n", room->name, priority, room->weight);
		if (room == farm->rooms[farm->count_rooms - 1])
		{
			// t_list *path_lst = room->paths;
			// while (path_lst)
			// {
			// 	// ft_dlst_push_back((t_dlist*)path_lst->content, ft_create_node_ptr(room));
			// 	show_path_((t_path*)path_lst->content);
			// 	path_lst = path_lst->next;
			// }
			if ((result = find_best_combination(room->paths, paths_combs, count)))
				return (result);
		}
		else
			path_selection(farm, room, priority, pqueue);
	}
	return (NULL);
}

t_list	*copy_paths(t_list *paths)
{
	t_list *cur;
	t_list *new;

	cur = paths;
	while (cur)
	{
		ft_lstpush(&new, ft_lstnew_ptr(cur->content));
		cur = cur->next;
	}
	return (new);
}

t_path	**find_best_combination(t_list *paths, t_path ***paths_combs, int count)
{
	int		i;
	t_list	*new;
	t_list	*path_lst;
	t_list	*result;
	t_path	*path;

	i = 0;
	while (paths_combs[i][0] && i < count)
		i++;
	if (i < count)
	{
		new = copy_paths(paths);

		path_lst = new;
		while (path_lst)
		{	
			path = (t_path*)path_lst->content;


			path_lst = path_lst->next;
		}
	}
}
