/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_comb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:00:26 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/09 16:15:43 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline static int	find_idx(t_dlist *paths, t_node *node)
{
	int		i;
	t_node	*cur;

	i = 0;
	cur = paths->head;
	while (cur)
	{
		if (cur == node)
			return (i);
		cur = cur->next;
		i++;
	}
	return (-1);
}

inline static int	find_comb_helper(
	t_farm *farm, t_stack *result, t_node *next_path_node, int need_path)
{
	while (next_path_node)
	{
		if (find_comb(farm, result, next_path_node, need_path))
			return (true);
		next_path_node = next_path_node->next;
	}
	return (false);
}

bool				find_comb(
	t_farm *farm, t_stack *result, t_node *cur_path_node, int need_path)
{
	int		i;
	int		cur_idx;
	int		value;
	t_node	*next_path_node;

	if (!cur_path_node)
		return (false);
	while (cur_path_node)
	{
		i = -1;
		cur_idx = find_idx(
			farm->rooms[farm->count_rooms - 1]->paths, cur_path_node);
		while (++i < result->len)
			if (farm->intersections[result->head[i]][cur_idx])
				return (false);
		ft_stack_push(result, cur_idx);
		if (result->len == result->size)
			return (true);
		next_path_node = cur_path_node->next;
		if (find_comb_helper(farm, result, next_path_node, need_path))
			return (true);
		ft_stack_pop(result, &value);
		cur_path_node = cur_path_node->next;
	}
	return (false);
}
