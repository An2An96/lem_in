/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l4_find_unique_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:11:32 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/09 16:50:04 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline static void	add_room_in_queue(
	t_farm *farm, t_dlist *queue, t_room *neighbor)
{
	if (neighbor->types & ROOM_END)
	{
		check_intersections(farm);
		ft_dlst_push_back(queue, ft_create_node_ptr(neighbor));
	}
	else
		ft_dlst_push_front(queue, ft_create_node_ptr(neighbor));
}

static bool			send_path_to_neighbors(
	t_farm *farm, t_room *room, t_path *path, t_dlist *queue)
{
	bool	opu;
	t_path	*path_copy;
	t_list	*neighbor_lst;
	t_room	*neighbor;

	opu = false;
	path_copy = make_path_copy(path);
	neighbor_lst = room->neighbors;
	while (neighbor_lst)
	{
		neighbor = farm->rooms[*LIST(neighbor_lst, int*)];
		neighbor_lst = neighbor_lst->next;
		if (neighbor->types & ROOM_START || find_cycle(path_copy, neighbor))
			continue ;
		ft_dlst_push_back(neighbor->paths,
			ft_create_node_ptr(!opu ? path : make_path_copy(path_copy)));
		opu = true;
		if (neighbor->types & ROOM_END)
			ft_dlst_push_back(LIST(neighbor->paths->tail, t_path*),
				ft_create_node_ptr(neighbor));
		add_room_in_queue(farm, queue, neighbor);
	}
	ft_dlst_del(&path_copy, NULL);
	return (opu);
}

static void			enter_room(t_farm *farm, t_room *room, t_dlist *queue)
{
	t_node	*path_lst;
	t_node	*next;
	t_path	*path;

	path_lst = room->paths->head;
	while (path_lst)
	{
		path = LIST(path_lst, t_path*);
		if (!(room->types & ROOM_START))
			ft_dlst_push_back(path, ft_create_node_ptr(room));
		next = path_lst->next;
		ft_dlst_remove_node(room->paths, path_lst,
			send_path_to_neighbors(farm, room, path, queue)
			? NULL : free_paths);
		path_lst = next;
	}
}

static int			find_and_check_comb(
	t_farm *farm, t_room *room, t_path_comb *paths_combs, int count)
{
	int		i;
	int		comb;
	t_stack *result;

	comb = farm->cur_comb;
	SECURE_MALLOC(result = ft_stack_new(comb + 1));
	if (find_comb(farm, result, room->paths->head, comb + 1))
	{
		i = -1;
		while (++i < result->len)
			paths_combs[comb].paths[i] =
				ft_dlst_get(room->paths, result->head[result->len - i - 1]);
		ft_stack_delete(result);
		paths_combs[comb].steps =
			get_steps_for_comb(&paths_combs[comb], farm->ants_count);
		IS_FLAG(FLAG_DEBUG)
			&& ft_printf("[DEBUG]: Complete %d/%d comb, steps: %d\n",
				comb + 1, count, paths_combs[comb].steps);
		return ((farm->cur_comb > 0
			&& paths_combs[comb - 1].steps < paths_combs[comb].steps)
			|| ++farm->cur_comb == count || farm->cur_comb >= farm->max_paths);
	}
	else
		ft_stack_delete(result);
	return (0);
}

t_path_comb			*find_unique_paths(t_farm *farm, int count)
{
	t_dlist		*queue;
	t_room		*room;
	t_path		*path;
	t_path_comb	*paths_combs;

	SECURE_MALLOC(queue = ft_dlst_create());
	paths_combs = allocate_mem_for_paths_combs(count);
	SECURE_MALLOC(path = ft_dlst_create());
	ft_dlst_push_front(farm->rooms[0]->paths, ft_create_node_ptr(path));
	ft_dlst_push_front(queue, ft_create_node_ptr(farm->rooms[0]));
	while (queue->tail && (room = LIST(queue->tail, t_room*)))
	{
		ft_dlst_remove_node(queue, queue->tail, NULL);
		if (room == farm->rooms[farm->count_rooms - 1])
		{
			if (find_and_check_comb(farm, room, paths_combs, count))
				break ;
		}
		else
			enter_room(farm, room, queue);
	}
	ft_dlst_del(&queue, NULL);
	return (paths_combs);
}
