/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_comb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:00:26 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/06 18:22:01 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static bool	find_intersection(t_path *first, t_path *second)
{
	t_node *fst_node;
	t_node *snd_node;

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
	return (false);
}

bool		find_comb(
	t_dlist *paths, t_path_comb *result, int cur_path, int need_path)
{
	int		i;
	bool	intercept;
	t_node	*cur_path_node;

	cur_path_node = paths->head;
	while (cur_path_node)
	{
		i = -1;
		intercept = false;
		while (++i < cur_path && !intercept)
			intercept = find_intersection(
				result->paths[i], LIST(cur_path_node, t_path*));
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
