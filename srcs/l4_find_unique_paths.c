/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l4_find_unique_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:11:32 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/06 15:35:11 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			find_cycle(t_path *path, t_room *room)
{
	t_node	*cur;

	cur = path->head;
	if (path)
	{
		cur = path->head;
		while (cur)
		{
			if (LIST(cur, t_room*) == room)
				return (true);
			cur = cur->next;
		}
	}
	return (false);
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

t_path		*make_path_copy(t_path *path)
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

t_path_comb	*allocate_mem_for_paths_combs(int count)
{
	int			i;
	t_path_comb	*paths_combs;

	i = 0;
	paths_combs = (t_path_comb*)ft_memalloc((count + 1) * sizeof(t_path_comb));
	while (i < count)
	{
		// paths_combs[i] = (t_path_comb*)ft_memalloc((i + 1) * sizeof(t_path_comb));
		paths_combs[i].paths = (t_path**)ft_memalloc((i + 1 + 1) * sizeof(t_path*));
		paths_combs[i].count = i + 1;
		i++;
	}
	return (paths_combs);
}

static bool	find_intersection(t_path *first, t_path *second)
{
	t_node *fst_node;
	t_node *snd_node;

	// ft_printf("find_intersection\n\nfirst path:\n");
	// show_path(first);
	// ft_printf("second path:\n");
	// show_path(second);

	if (!first || !second)
		return (false);
	if (first == second)
		return (true);
	fst_node = first->head;
	while (fst_node)
	{
		snd_node = second->head;
		while (snd_node && snd_node->next)
		{
			if (fst_node->content == snd_node->content)
				return (true);
			snd_node = snd_node->next;
		}
		fst_node = fst_node->next;
	}
	// ft_printf("no intersection!!\n");
	return (false);
}

static bool	find_comb(
	t_dlist *paths, t_path_comb *result, int cur_path, int need_path)
{
	int		i;
	bool	intercept;
	t_node	*cur_path_node;

	cur_path_node = paths->head;
	while (cur_path_node)
	{
		i = 0;
		intercept = false;
		while (i < cur_path && !intercept)
		{
			intercept = find_intersection(
				result->paths[i], LIST(cur_path_node, t_path*));
			i++;
		}
		if (!intercept)
		{
			result->paths[cur_path] = (t_path*)cur_path_node->content;
			if (cur_path + 1 >= need_path
				|| find_comb(paths, result, cur_path + 1, need_path))
				return (true);
			result->paths[cur_path] = NULL;
		}
		cur_path_node = cur_path_node->next;
	}
	return (false);
}

static void	path_selection(
	t_farm *farm, t_room *room, int old_priority, t_pqueue *pqueue)
{
	t_node	*path_lst;
	t_list	*neighbor_lst;
	t_path	*path;
	t_path	*path_copy;
	t_room	*neighbor;
	bool	original_path_lst_usage;
	int		i;

	i = 0;
	path_lst = room->paths->head;
	while (path_lst)
	{
		original_path_lst_usage = false;
		path = LIST(path_lst, t_path*);
		if (IS_FLAG(FLAG_DEBUG))
		{
			ft_printf("\x1b[1;31mCheck path %d\x1b[0m\n", i);
			show_path(path);
		}
		if (!room->processed_paths[i])
		{
			if (IS_FLAG(FLAG_DEBUG))
				ft_printf("\x1b[32;01mNot processed\x1b[0m\n");
			if (!(room->types & ROOM_START))
				ft_dlst_push_back(path, ft_create_node_ptr(room));
			path_copy = make_path_copy(path);
			neighbor_lst = room->neighbors;
			while (neighbor_lst)
			{
				neighbor = farm->rooms[*LIST(neighbor_lst, int*)];
				if (IS_FLAG(FLAG_DEBUG))
					ft_printf("select neighbor: %s\n", neighbor->name);
				if (!(neighbor->types & ROOM_START) && !find_cycle(path_copy, neighbor))
				{
					if (!original_path_lst_usage)
					{
						if (IS_FLAG(FLAG_DEBUG))
						{
							ft_printf("throw path to %s\n", neighbor->name);
							show_path(path);
						}
						ft_dlst_push_back(neighbor->paths, ft_create_node_ptr(path));
						original_path_lst_usage = true;
					}
					else
					{
						if (IS_FLAG(FLAG_DEBUG))
						{
							ft_printf("copy and throw path to %s\n", neighbor->name);
							show_path(path_copy);
						}
						ft_dlst_push_back(neighbor->paths, ft_create_node_ptr(make_path_copy(path_copy)));
					}
					if (neighbor->types & ROOM_END)
					{
						ft_dlst_push_back(LIST(neighbor->paths->tail, t_path*), ft_create_node_ptr(neighbor));
						pq_insert(pqueue, neighbor, 0);
					}
					else
						pq_insert(pqueue, neighbor, old_priority + neighbor->weight);
				}
				neighbor_lst = neighbor_lst->next;
			}
			room->processed_paths[i] = true;
			ft_dlst_del(&path_copy, NULL);
		}
		i++;
		path_lst = path_lst->next;
	}
	if (IS_FLAG(FLAG_DEBUG))
		ft_printf("\n\n");
		
}

t_path_comb		*find_unique_paths(t_farm *farm, int count)
{
	t_pqueue	*pqueue;
	t_room		*room;
	t_path		*path;
	int			priority;
	t_path_comb	*paths_combs;
	t_path		**result;

	paths_combs = allocate_mem_for_paths_combs(count);
	if (!(pqueue = pq_init(farm->count_rooms * 10, true)))
		throw_error(STR_ERROR_SYS, "Not enough memory");
	if (!(path = ft_dlst_create()))
		throw_error(STR_ERROR_SYS, "Not enough memory");
	ft_dlst_push_front(farm->rooms[0]->paths, ft_create_node_ptr(path));
	pq_insert(pqueue, farm->rooms[0], 0);
	while ((room = (t_room*)pq_extract_ex(pqueue, &priority)))
	{
		if (IS_FLAG(FLAG_DEBUG))
			ft_printf("\x1b[0;33mextract room %s [%d], weight: %d\x1b[0m\n", room->name, priority, room->weight);
		if (room == farm->rooms[farm->count_rooms - 1])
		{
			// ft_dlst_push_back(LIST(room->paths->tail, t_path*), ft_create_node_ptr(room));
			if (IS_FLAG(FLAG_DEBUG))
			{
				ft_printf("FIND NEW PATH:\n");
				show_path(LIST(room->paths->tail, t_path*));
				ft_printf("++++++++++++++\n");
			}
			

			if (find_comb(room->paths, &paths_combs[farm->cur_comb], 0, farm->cur_comb + 1))
			{
				paths_combs[farm->cur_comb].steps = get_steps_for_comb(
					&paths_combs[farm->cur_comb], farm->ants_count);
				if (IS_FLAG(FLAG_DEBUG))
					ft_printf("steps for %d comb: %d\n", farm->cur_comb, paths_combs[farm->cur_comb].steps);
				if ((farm->cur_comb > 0 && paths_combs[farm->cur_comb - 1].steps < paths_combs[farm->cur_comb].steps)
					|| ++farm->cur_comb == count)
					return (paths_combs);
			}
		}
		else
			path_selection(farm, room, priority, pqueue);
	}
	return (paths_combs);
}
