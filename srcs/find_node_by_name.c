/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_node_by_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 17:14:12 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/20 18:06:22 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_node	*find_node_by_name_helper(
	t_node **rooms, int start, int finish, char *name)
{
	int		idx;
	char	res;

	idx = start + ((finish - start) / 2);
	// ft_printf("%d, %d | %s - %s\n", start, finish, rooms[idx]->name, name);
	res = ft_strcmp(rooms[idx]->name, name);
	// ft_printf("res: %d\n", res);
	if (res > 0)
		return (find_node_by_name_helper(rooms, start, idx, name));
	else if (res < 0)
		return (find_node_by_name_helper(rooms, idx, finish, name));
	return (rooms[idx]);
}

t_node			*find_node_by_name(t_node **rooms, char *name)
{
	int i;

	if (!ft_strcmp(rooms[0]->name, name))
		return (rooms[0]);
	i = 0;
	while (rooms[i])
		i++;
	i--;
	// ft_printf("check %s\n", rooms[i]->name);
	if (!ft_strcmp(rooms[i]->name, name))
		return (rooms[i]);
	return (find_node_by_name_helper(rooms, 1, i - 1, name));
}

static int find_node_index_by_name_helper(
	t_node **rooms, int start, int finish, char *name)
{
	int		idx;
	char	res;

	idx = start + ((finish - start) / 2);
	res = ft_strcmp(rooms[idx]->name, name);
	if (res > 0)
		return (find_node_index_by_name_helper(rooms, start, idx - 1, name));
	else if (res < 0)
		return (find_node_index_by_name_helper(rooms, idx + 1, finish, name));
	return (idx);
}

int			find_node_index_by_name(t_node **rooms, char *name)
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