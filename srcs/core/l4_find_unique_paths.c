/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l4_find_unique_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:11:32 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/08 14:58:06 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline static void	add_path_room(t_room *room, t_path *path)
{
	ft_dlst_push_back(room->paths, ft_create_node_ptr(path));
}

static void			send_path_to_neighbors(
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
		add_path_room(neighbor, !opu ? path : make_path_copy(path_copy));
		opu = true;
		if (neighbor->types & ROOM_END)
			ft_dlst_push_back(LIST(neighbor->paths->tail, t_path*),
				ft_create_node_ptr(neighbor));
		if (neighbor->types & ROOM_END)
			ft_dlst_push_back(queue, ft_create_node_ptr(neighbor));
		else
			ft_dlst_push_front(queue, ft_create_node_ptr(neighbor));
	}
	ft_dlst_del(&path_copy, NULL);
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
		send_path_to_neighbors(farm, room, path, queue);
		next = path_lst->next;
		ft_dlst_remove_node(room->paths, path_lst, NULL);
		path_lst = next;
	}
}

static int			find_and_check_comb(
	t_farm *farm, t_room *room, t_path_comb *paths_combs, int count)
{
	int comb;

	comb = farm->cur_comb;
	IS_FLAG(FLAG_DEBUG)
		&& ft_printf("[find_and_check_comb] pathes: %d, need = %d\n",
			room->paths->size, comb + 1);
	if (find_comb(room->paths, &paths_combs[comb], room->paths->head, comb + 1))
	{
		paths_combs[comb].steps =
			get_steps_for_comb(&paths_combs[comb], farm->ants_count);
		IS_FLAG(FLAG_DEBUG)
			&& ft_printf("complete %d/%d comb, steps: %d\n",
				comb + 1, count, paths_combs[comb].steps);
		return ((farm->cur_comb > 0
			&& paths_combs[comb - 1].steps < paths_combs[comb].steps)
			|| ++farm->cur_comb == count);
	}
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