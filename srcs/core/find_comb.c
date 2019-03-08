/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_comb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:00:26 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/07 17:28:58 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static bool	find_intersection(t_path *first, t_path *second)
{
	// static size_t counter;

	// ft_putnbr(++counter);
	// write(1, "\n", 1);

	t_node *fst_node;
	t_node *snd_node;

	// ft_printf("find_intersection:\n");
	// show_path(first);
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
	return (false);
}

bool		find_comb(
	t_dlist *paths, t_path_comb *result, t_node *cur_path_node, int need_path)
{
	int		i;
	t_node	*next_path_node;

	// ft_printf("find_comb [%d/%d]\n", result->last_free_idx, need_path);
	// show_path(LIST(cur_path_node, t_path*));

	if (!cur_path_node)
		return (false);

	while (cur_path_node)
	{
		i = -1;
		while (++i < result->last_free_idx)
			if (find_intersection(result->paths[i], LIST(cur_path_node, t_path*)))
				return (false);
		result->paths[result->last_free_idx++] = (t_path*)cur_path_node->content;
		if (result->last_free_idx >= need_path)
			return (true);
		next_path_node = cur_path_node->next;
		while (next_path_node)
		{
			if (find_comb(paths, result, next_path_node, need_path))
				return (true);
			next_path_node = next_path_node->next;
		}
		result->paths[--result->last_free_idx] = NULL;
		cur_path_node = cur_path_node->next;
	}
	return (false);
}
