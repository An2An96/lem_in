/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:50:53 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/08 12:22:09 by rschuppe         ###   ########.fr       */
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

t_path_comb	*allocate_mem_for_paths_combs(int count)
{
	int			i;
	t_path_comb	*paths_combs;

	i = 0;
	SECURE_MALLOC(paths_combs =
		(t_path_comb*)ft_memalloc((count + 1) * sizeof(t_path_comb)));
	while (i < count)
	{
		SECURE_MALLOC(paths_combs[i].paths =
			(t_path**)ft_memalloc((i + 1 + 1) * sizeof(t_path*)));
		paths_combs[i].count = i + 1;
		i++;
	}
	return (paths_combs);
}

t_path		*make_path_copy(t_path *path)
{
	t_path	*new;
	t_node	*cur;

	new = NULL;
	if (path)
	{
		SECURE_MALLOC(new = ft_dlst_create());
		cur = path->head;
		while (cur)
		{
			ft_dlst_push_back(new, ft_create_node_ptr(cur->content));
			cur = cur->next;
		}
	}
	return (new);
}
