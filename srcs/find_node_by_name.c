/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_node_by_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 17:14:12 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/08 13:09:52 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	find_node_idx_by_name_helper(
	t_room **rooms, int start, int finish, char *name)
{
	int		idx;
	char	res;

	if (start > finish)
		return (-1);
	idx = start + ((finish - start) / 2);
	res = ft_strcmp(rooms[idx]->name, name);
	if (res > 0)
		return (find_node_idx_by_name_helper(rooms, start, idx - 1, name));
	else if (res < 0)
		return (find_node_idx_by_name_helper(rooms, idx + 1, finish, name));
	return (idx);
}

t_room		*find_node_by_name(t_room **rooms, int count_rooms, char *name)
{
	int idx;

	if (!ft_strcmp(rooms[0]->name, name))
		return (rooms[0]);
	if (!ft_strcmp(rooms[count_rooms - 1]->name, name))
		return (rooms[count_rooms - 1]);
	idx = find_node_idx_by_name_helper(rooms, 1, count_rooms - 1, name);
	return (idx >= 0 ? rooms[idx] : NULL);
}

int			find_node_idx_by_name(t_room **rooms, int count_rooms, char *name)
{
	if (!ft_strcmp(rooms[0]->name, name))
		return (0);
	if (!ft_strcmp(rooms[count_rooms - 1]->name, name))
		return (count_rooms - 1);
	return (find_node_idx_by_name_helper(rooms, 1, count_rooms - 1, name));
}
