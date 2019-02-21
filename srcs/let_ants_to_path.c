/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_ants_to_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:25:43 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/21 18:09:09 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	let_ants_to_path(t_path **path, t_node *rooms, t_farm *farm)
{
	int	finished_ants;
	int index;
	int	nbr_ants;
	int pos;

	finished_ants = 0;
	nbr_ants = 1;
	pos = path[0]->count_node;
	index = path[0]->idx[pos];
	while (finished_ants <= farm->ants_count)
	{	
		while (pos)
		{
			if (farm->rooms[index]->ant_num == 0)
			{
				if (farm->rooms[path[0]->idx[pos - 1]]->ant_num != 0)
				{
					farm->rooms[index]->ant_num = nbr_ants;
					farm->rooms[path[0]->idx[pos - 1]]->ant_num = 0;
					index = path[0]->idx[pos--];
				}
			}
			pos--;
		}	
	}
}