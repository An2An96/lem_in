/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_node_by_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 17:14:12 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/25 19:38:05 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	find_node_index_by_name_helper(
	t_room **rooms, int start, int finish, char *name)
{
	int		idx;
	char	res;

	if (start > finish)
		return (-1);
	idx = start + ((finish - start) / 2);
	res = ft_strcmp(rooms[idx]->name, name);
	if (res > 0)
		return (find_node_index_by_name_helper(rooms, start, idx - 1, name));
	else if (res < 0)
		return (find_node_index_by_name_helper(rooms, idx + 1, finish, name));
	return (idx);
}

t_room		*find_node_by_name(t_room **rooms, char *name)
{
	int i;
	int idx;

	if (!ft_strcmp(rooms[0]->name, name))
		return (rooms[0]);
	i = 0;
	while (rooms[i])	//	ОПТИМИЗИРОВАТЬ
		i++;
	i--;
	if (!ft_strcmp(rooms[i]->name, name))
		return (rooms[i]);
	idx = find_node_index_by_name_helper(rooms, 1, i - 1, name);
	return (idx >= 0 ? rooms[idx] : NULL);
}

int			find_node_index_by_name(t_room **rooms, char *name)
{
	int i;

	if (!ft_strcmp(rooms[0]->name, name))
		return (0);
	i = 0;
	while (rooms[i])
		i++;
	i--;
	if (!ft_strcmp(rooms[i]->name, name))
		return (i);
	return (find_node_index_by_name_helper(rooms, 1, i - 1, name));
}
