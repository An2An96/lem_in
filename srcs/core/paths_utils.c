/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:50:53 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/06 22:17:32 by rschuppe         ###   ########.fr       */
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
