/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 21:47:32 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/05 15:40:19 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_split_result(char **res)
{
	int i;

	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);
}

void	show_path(t_path *path)
{
	t_node	*cur;

	cur = path->head;
	while (cur)
	{
		ft_printf("%s%s", cur != path->head ? " -> " : "",  ((t_room*)cur->content)->name);
		cur = cur->next;
	}
	ft_printf("\n");
}
