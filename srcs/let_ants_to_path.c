/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_ants_to_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:25:43 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/21 19:30:44 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	let_ants_to_path(t_path **path, t_node *rooms, t_farm *farm)
{
	int	finished_ants;
	// int index;
	int	nbr_ants;
	int pos;

	finished_ants = 0;
	nbr_ants = 1;
	// pos = path[0]->count_node;
	// index = path[0]->idx[pos];
	while (finished_ants <= farm->ants_count)
	{
		pos = path[0]->count_node;
		while (pos) // идем с финиша в сторону старта
		{
			if (farm->rooms[ path[0]->idx[pos] ]->ant_num == 0)
			{
				if (farm->rooms[ path[0]->idx[pos - 1] ]->ant_num != 0) // если в предшествующей комнате есть муравей
				{
					farm->rooms[ path[0]->idx[pos] ]->ant_num = farm->rooms[ path[0]->idx[pos - 1] ]->ant_num;
					if (pos == 1) // если предшествующая комната это старт
						farm->rooms[ path[0]->idx[0] ]->ant_num = ++nbr_ants;
					else
						farm->rooms[ path[0]->idx[pos - 1] ]->ant_num = 0;
					// index = path[0]->idx[pos--];
				}
			}
			if (farm->rooms[ path[0]->count_node ]->ant_num != 0)
			{
				farm->rooms[ path[0]->count_node ]->ant_num = 0;
				finished_ants++;
			}
			pos--;
		}	
	}
}